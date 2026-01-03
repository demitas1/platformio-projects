# STM32 Blackpill LED Blink with FreeRTOS

STM32F411CE Blackpillボードのオンボード青色LED（PC13）をFreeRTOSタスクで1秒間隔で点滅させるプロジェクト。

## ハードウェア

- **ボード**: WeAct Studio BlackPill V2.0 (STM32F411CE)
- **MCU**: STM32F411CEU6 (100MHz, 128KB RAM, 512KB Flash)
- **LED**: PC13 (オンボード青色LED、アクティブLow)
- **デバッガ**: ST-Link V2

## ソフトウェアスタック

- **フレームワーク**: STM32Cube HAL
- **RTOS**: FreeRTOS 10.3.1
- **ポート**: ARM_CM3 (Cortex-M3/M4互換)

## プロジェクト構成

```
led-blink-free-rtos/
├── platformio.ini          # プロジェクト設定
├── include/                # プロジェクトヘッダー
├── src/
│   └── main.c              # メインソース（FreeRTOSタスク）
└── lib/
    └── FreeRTOS/           # FreeRTOSライブラリ
        ├── library.json    # ライブラリ設定
        ├── FreeRTOSConfig.h
        └── src/            # FreeRTOSソース
```

## ビルド

```bash
cd projects/stm32/led-blink-free-rtos
pio run
```

## 書き込み

ST-Link V2をBlackpillに接続し、以下を実行：

```bash
pio run -t upload
```

## FreeRTOS設定

`lib/FreeRTOS/FreeRTOSConfig.h` で設定：

- ヒープサイズ: 32KB
- Tick周期: 1000Hz (1ms)
- 最大優先度: 5
- スタックサイズ: 128ワード

## led-blinkとの違い

| 項目 | led-blink | led-blink-free-rtos |
|------|-----------|---------------------|
| 遅延 | HAL_Delay() | vTaskDelay() |
| メインループ | while(1) | FreeRTOSタスク |
| RAM使用 | 44 bytes | 33KB |
| Flash使用 | 3.4KB | 6.2KB |

## 動作確認

書き込み後、オンボードの青色LEDが1秒間隔で点滅すれば成功。

## 備考：FreeRTOSソースをプロジェクトに含めた理由

### 問題の経緯

STM32Cubeフレームワーク（`~/.platformio/packages/framework-stm32cubef4/`）にはFreeRTOSが含まれているが、PlatformIOでは自動的に有効にならない。外部パスからFreeRTOSソースを参照する方法を試みたが、以下の問題が発生した。

### 発生した問題

1. **VFPフラグの不整合**

   `build_src_filter`で外部パスのFreeRTOSソースをビルドに含めると、FreeRTOSソースには`-mfloat-abi=hard -mfpu=fpv4-sp-d16`が適用されるが、HALドライバやスタートアップコードにはデフォルト設定（soft float）が適用される。リンク時にVFPレジスタの不整合エラーが発生。

   ```
   error: xxx.o uses VFP register arguments, firmware.elf does not
   ```

2. **ARM_CM4F（FPU対応）ポートのアセンブラエラー**

   Cortex-M4F用ポート（`portable/GCC/ARM_CM4F/port.c`）はFPUレジスタの保存/復元にVFP命令を使用する。PlatformIOのデフォルト設定では`-mcpu=cortex-m4`のみでFPUフラグが含まれないため、アセンブラエラーが発生。

   ```
   Error: selected processor does not support `vstmdbeq r0!,{s16-s31}' in Thumb mode
   ```

### 解決策

1. **FreeRTOSソースをプロジェクト内にコピー**

   `lib/FreeRTOS/`にソースを配置することで、プロジェクト全体で一貫したコンパイルフラグが適用される。

2. **ARM_CM3ポートを使用**

   FPU命令を使用しないARM_CM3ポートを採用。Cortex-M4でも問題なく動作する（FPUコンテキストの保存は行われない）。

### 代替案（未検証）

- `board_build.mcu`や`build_flags`でFPUを明示的に有効化し、ARM_CM4Fポートを使用する方法もあるが、フレームワーク全体の再ビルドが必要になる可能性がある。
