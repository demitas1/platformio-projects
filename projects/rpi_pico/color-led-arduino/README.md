# RGB LED レインボーデモ (Raspberry Pi Pico)

FreeRTOSタスクを使用したRGB LEDのレインボーカラーアニメーションデモ。

## 概要

HSV色空間の色相(Hue)を0〜359度で連続的に変化させ、RGB LEDでレインボーカラーを表現します。

## ハードウェア

### 必要部品

- Raspberry Pi Pico
- RGB LED（カソードコモンまたはアノードコモン）
- 抵抗 3本（LEDに応じて適切な値）

### デフォルトピン配置

| 色 | GPIO | ピン番号 |
|----|------|----------|
| R  | GP10 | 14       |
| G  | GP14 | 19       |
| B  | GP15 | 20       |

## ビルド・書き込み

```bash
# ビルド
pio run

# 書き込み（BOOTSELボタンを押しながらUSB接続後）
pio run -t upload

# シリアルモニター
pio device monitor
```

## GPIOピンの変更

`platformio.ini` の `build_flags` でピンを上書きできます：

```ini
build_flags =
    -DPIO_FRAMEWORK_ARDUINO_ENABLE_FREERTOS
    -DLED_PIN_R=2
    -DLED_PIN_G=3
    -DLED_PIN_B=4
```

## ファイル構成

| ファイル | 説明 |
|----------|------|
| `main.cpp` | FreeRTOSタスクでレインボーアニメーション実行 |
| `hsv.cpp/h` | HSV→RGB色変換 |
| `led_pwm.cpp/h` | PWMによるLED制御 |

## 技術詳細

- **フレームワーク**: Arduino (earlephilhowerコア)
- **RTOS**: FreeRTOS
- **PWM制御**: Arduino `analogWrite()` (8bit解像度)
- **更新間隔**: 50ms（約18秒で1周期）
