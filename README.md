# PlatformIO Projects

ESP32マイコン向けのPlatformIO開発環境リポジトリ。ESP-IDFフレームワークを使用。

## 必要環境

- Python 3.12以上
- PlatformIO Core

## セットアップ

```bash
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

## プロジェクト構成

```
projects/
└── esp32/
    └── led-blink/    # LED点滅プログラム
```

## 基本コマンド

プロジェクトディレクトリ内で実行:

```bash
# ビルド
pio run

# デバイスへ書き込み
pio run -t upload

# シリアルモニター
pio device monitor
```

## 新規プロジェクト作成

```bash
cd projects/esp32
mkdir <project-name>
cd <project-name>
pio project init --board esp32dev --project-option "framework=espidf"
```

`platformio.ini`にシリアルポート設定を追加:

```ini
monitor_speed = 115200
upload_port = /dev/ttyUSB0
monitor_port = /dev/ttyUSB0
```
