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
- **ポート**: ARM_CM4F (Cortex-M4 FPU対応)

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
            └── portable/GCC/ARM_CM4F/  # FPU対応ポート
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

STM32Cubeフレームワーク（`~/.platformio/packages/framework-stm32cubef4/`）にはFreeRTOSが含まれているが、PlatformIOでは自動的に有効にならない。`lib_deps = FreeRTOS`を指定するとPlatformIOレジストリからダウンロードされるが、インクルードパスが自動解決されないためビルドに失敗する。

### 発生した問題

1. **lib_depsでのインクルードパス問題**

   `lib_deps = FreeRTOS`でライブラリが自動ダウンロードされるが、`#include "FreeRTOS.h"`が解決されない。

2. **ARM_CM4F（FPU対応）ポートのアセンブラエラー**

   PlatformIOのデフォルト設定では`-mfpu`や`-mfloat-abi`フラグが含まれないため、FPU命令を使用するARM_CM4Fポートでアセンブラエラーが発生する。

   ```
   Error: selected processor does not support `vstmdbeq r0!,{s16-s31}' in Thumb mode
   ```

### 解決策

1. **FreeRTOSソースをプロジェクト内にコピー**

   `lib/FreeRTOS/`にソースを配置し、`build_flags`でインクルードパスを明示的に指定。

2. **FPUフラグを追加してARM_CM4Fポートを使用**

   `platformio.ini`に以下のフラグを追加することで、ARM_CM4F（FPU対応）ポートが使用可能になる：

   ```ini
   build_flags =
       -I lib/FreeRTOS/src/include
       -I lib/FreeRTOS/src/portable/GCC/ARM_CM4F
       -mthumb
       -mfpu=fpv4-sp-d16
       -mfloat-abi=softfp
   ```

   - `-mfpu=fpv4-sp-d16`: STM32F4のFPU（単精度）を指定
   - `-mfloat-abi=softfp`: ソフトフロートABI（FPU命令は使用するが関数呼び出しはソフト）

### 関連するPlatformIO GitHub Issue

- [Issue #591: Make FPU and CMSIS-DSP configuration easier](https://github.com/platformio/platform-ststm32/issues/591) - **OPEN**
  - STM32CubeビルダーがFPUフラグを自動設定しない問題。根本的な解決は未実施。

- [Issue #285: FreeRTOS with stm32cube framework on NucleoF767ZI](https://github.com/platformio/platform-ststm32/issues/285) - **CLOSED**
  - 本プロジェクトで採用した解決策（`-mfloat-abi=softfp`）の情報源。
