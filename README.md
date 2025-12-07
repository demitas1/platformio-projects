# PlatformIO Projects

マイコンプラットフォーム向けのPlatformIO開発環境リポジトリ。

## 対応プラットフォーム

| プラットフォーム | フレームワーク | ボード |
|-----------------|---------------|--------|
| ESP32 | ESP-IDF | esp32dev |
| Raspberry Pi Pico | Arduino (earlephilhower) | pico |

## 必要環境

- Python 3.12以上
- PlatformIO Core

## セットアップ

```bash
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

### Linux udevルール設定

USBデバイスへのアクセスにudevルールが必要:

```bash
# PlatformIO udevルールをインストール
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules

# udevをリロード
sudo udevadm control --reload-rules
sudo udevadm trigger

# ユーザーをグループに追加（要ログアウト/ログイン）
sudo usermod -aG plugdev $USER
sudo usermod -aG dialout $USER
```

## プロジェクト構成

```
projects/
├── esp32/
│   └── led-blink/    # LED点滅プログラム (ESP-IDF)
└── rpi_pico/
    └── led-blink/    # LED点滅プログラム (Arduino + FreeRTOS)
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

### ESP32

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

### Raspberry Pi Pico

```bash
cd projects/rpi_pico
mkdir <project-name>
cd <project-name>
pio project init --board pico
```

`platformio.ini`を以下のように編集:

```ini
[env:pico]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = pico
framework = arduino
board_build.core = earlephilhower
build_flags =
    -DPIO_FRAMEWORK_ARDUINO_ENABLE_FREERTOS
monitor_speed = 115200
```

**アップロード方法**: BOOTSELボタンを押しながらUSBケーブルを接続してから `pio run -t upload` を実行。
