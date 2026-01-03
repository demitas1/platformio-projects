# STM32 Blackpill LED Blink

STM32F411CE Blackpillボードのオンボード青色LED（PC13）を1秒間隔で点滅させるプロジェクト。

## ハードウェア

- **ボード**: WeAct Studio BlackPill V2.0 (STM32F411CE)
- **MCU**: STM32F411CEU6 (100MHz, 128KB RAM, 512KB Flash)
- **LED**: PC13 (オンボード青色LED、アクティブLow)
- **デバッガ**: ST-Link V2

## 環境セットアップ

### udevルール（Linux）

ST-Linkにアクセスするためのudevルールをインストール：

```bash
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
sudo udevadm control --reload-rules
sudo udevadm trigger
```

ユーザーをグループに追加（要再ログイン）：

```bash
sudo usermod -aG plugdev $USER
sudo usermod -aG dialout $USER
```

## ビルド

```bash
cd projects/stm32/led-blink
pio run
```

## 書き込み

ST-Link V2をBlackpillに接続し、以下を実行：

```bash
pio run -t upload
```

## 接続図

```
ST-Link V2          Blackpill
---------           ---------
3.3V       ------>  3V3
GND        ------>  GND
SWCLK      ------>  SWCLK
SWDIO      ------>  SWDIO
```

## 動作確認

書き込み後、オンボードの青色LEDが1秒間隔で点滅すれば成功。
