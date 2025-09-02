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

## Controls
Tap GPIO 18: Previous  · Hold GPIO 18 Volume Down
Tap GPIO 19: Play/Pause      
Tap GPIO 21: Next      · Hold GPIO 19 Volume Up

