# LED Blink (Raspberry Pi Pico)

FreeRTOSを使用したLED点滅プログラム。

## 概要

- オンボードLED (GPIO 25) を500ms間隔で点滅
- FreeRTOSタスクで制御
- シリアル出力でLED状態を表示

## ビルド・実行

```bash
# ビルド
pio run

# アップロード（BOOTSELモードで接続）
pio run -t upload

# シリアルモニター
pio device monitor
```

## アップロード方法

1. PicoのBOOTSELボタンを押しながらUSBケーブルを接続
2. `pio run -t upload` を実行
3. 書き込み完了後、自動的に再起動

## シリアル出力例

```
Starting LED Blink with FreeRTOS
LED ON
LED OFF
LED ON
LED OFF
...
```

## ファイル構成

- `src/main.cpp` - メインプログラム（FreeRTOSタスク）
- `platformio.ini` - PlatformIO設定
