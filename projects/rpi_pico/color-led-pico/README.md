# color-led-pico

Raspberry Pi Pico用のRGB LEDレインボーデモ。Pico SDK（baremetalフレームワーク）を使用。

## 概要

HSV色空間でHue（色相）を0〜359度で変化させ、RGB LEDでレインボーカラーを表示する。

## 使用プラットフォーム

- **Platform**: [wizio-pico](https://github.com/maxgerhardt/wizio-pico.git)
- **Framework**: baremetal (Pico SDK)
- **Board**: raspberry-pi-pico

## ハードウェア接続

| 機能 | GPIO |
|------|------|
| LED赤 | GP10 |
| LED緑 | GP14 |
| LED青 | GP15 |

GPIOピンは `src/led_pwm.h` で変更可能。

## ファイル構成

```
src/
├── main.c      - メインループ（レインボー表示）
├── hsv.c/h     - HSV→RGB変換
└── led_pwm.c/h - PWM制御（Pico SDK hardware/pwm.h使用）
```

## ビルド・書き込み

```bash
# ビルド
pio run

# 書き込み
# 1. BOOTSELボタンを押しながらUSB接続
# 2. RPI-RP2ドライブがマウントされたことを確認
lsblk | grep RPI-RP2
# 3. アップロード実行
pio run -t upload

# シリアルモニター
pio device monitor
```

### マウント確認

BOOTSELモードで接続すると `RPI-RP2` というUSBドライブがマウントされる。

```bash
# マウント確認
lsblk | grep RPI-RP2
# 出力例: └─sdc1  8:33  1  128M  0 part /media/username/RPI-RP2

# または
ls /media/$USER/
# RPI-RP2 が表示されればOK
```

マウントされない場合はBOOTSELボタンを押しながら再接続する。

## 関連プロジェクト

- `../color-led-arduino/` - Arduino版（earlephilhowerコア使用）
- `../../esp32/color-led/` - ESP32版（ESP-IDF使用）
