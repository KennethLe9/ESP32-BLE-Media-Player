# ESP32 BLE Media Player
3-Button Bluetooth Media Player (Prev/Next, Play/Pause, Volume). Compatible with any Device via Bluetooth.

## Features
3 buttons to control music and long-press to control volume
LED feedback on ESP32 for press and long-press
Works on Spotify and YouTube 

## Parts
ESP32 Dev Board, 3x four pin pushbuttons, breadboard, male-to-male jumper cables

## Pinout
| Function   | ESP32 GPIO | Wiring                                    |
|------------|:----------:|-------------------------------------------|
| Previous   | 18         | Terminal A → GPIO18, Terminal B → GND     |
| Play/Pause | 19         | Terminal A → GPIO19, Terminal B → GND     |
| Next       | 21         | Terminal A → GPIO21, Terminal B → GND     |
| LED        | 2          | Onboard / external LED on GPIO2           |

## Build
1. Arduino IDE → Boards Manager → install **ESP32 by Espressif (2.0.14)**  
2. Install **ESP32 BLE Keyboard (T-vK) on Github** → Sketch → Include Library → Add .Zip Library → Upload **ESP32 BLE Keyboard (T-vK) ZIP**
3. Select your board (e.g., DOIT ESP32 DEVKIT V1) → Upload Sketch
4. Pair **ESP32 Media Remote** in Bluetooth settings

## Controls
- **GPIO 18** — Tap: Previous · Hold: Volume Down
- **GPIO 19** — Tap: Play/Pause
- **GPIO 21** — Tap: Next · Hold: Volume Up

## Troubleshooting
- **Compile error (std::string → String)**: use ESP32 core **2.0.14**
- **No response on Button Press**: check wiring
- 
[![Watch the 20s demo](docs/demopicture.jpg)](https://youtu.be/N8l9O_iFldo?si=ke38ry5I1bNIJLMo)

## License
MIT

