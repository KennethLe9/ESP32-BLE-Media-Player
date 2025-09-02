# ESP32 BLE Media Player
3-Button Bluetooth Media Player (Prev/Next, Play/Pause, Volume). Compatible with any Device via Bluetooth.

## Features
3 buttons to control music and long-press to control volume
LED feedback on ESP32 for press and long-press
Works on Spotify and YouTube 

## Pinout
| Function   | ESP32 GPIO | Wiring                                    |
|------------|:----------:|-------------------------------------------|
| Previous   | 18         | Button A → GPIO18, Button B → GND         |
| Play/Pause | 19         | Button A → GPIO19, Button B → GND         |
| Next       | 21         | Button A → GPIO21, Button B → GND         |
| LED        | 2          | Onboard / external LED on GPIO2           |

