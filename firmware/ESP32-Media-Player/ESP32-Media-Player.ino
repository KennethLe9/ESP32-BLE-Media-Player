// ESP32 BLE Media Remote — Library version with Button(int) constructor
// Mapping: 18=Prev (hold: Vol-), 19=Play/Pause, 21=Next (hold: Vol+)
// Wire each button: GPIO ↔ button ↔ GND (uses INPUT_PULLUP)

#include <BleKeyboard.h> //Using the ESP32 BLE Keyboard library 

const int Previous_Track = 18;
const int Play_Pause = 19;
const int Next_Track = 21;

const unsigned long debounce_ms = 10; //button clicking speed
const unsigned long holdpress_ms = 300; //holding the button speed
const unsigned long repeat_ms = 150;//for volume step speed

