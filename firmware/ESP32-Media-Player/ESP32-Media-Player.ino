// ESP32 BLE Media Remote — Library version with Button(int) constructor
// Mapping: 18=Prev (hold: Vol-), 19=Play/Pause, 21=Next (hold: Vol+)
// Wire each button: GPIO ↔ button ↔ GND (uses INPUT_PULLUP)

#include <BleKeyboard.h> //Using the ESP32 BLE Keyboard library 

BleKeyboard bleKeyboard;

const int Previous_Track = 18;
const int Play_Pause = 19;
const int Next_Track = 21;
const int LED_Light = 2;// using the built in esp32 light 

const unsigned long debounce_ms = 10; //button clicking speed
const unsigned long holdpress_ms = 300; //holding the button speed
const unsigned long repeat_ms = 250;//for volume step speed

struct Button { //info that button needs: pin, if it is pressed, or hold, when is it press and released 
  int pin; //what pin is it located
  int Stabled; // debounced state High = idle and Low = Pressed
  int read; //to tell what is going on
  unsigned long LastChanged; //when changed happend
  unsigned long pressedAt; //time when the pressing began
  unsigned long LastRepeated;//for the volume feature 
  bool isPressed, isActive; //boolean to test what is going on

  Button(int gpio)
  : pin(gpio),
    Stabled(HIGH),
    read(HIGH),
    LastChanged(0),
    pressedAt(0),
    LastRepeated(0),
    isPressed(false),
    isActive(false){} //default setting
  Button() : Button(-1){}//Button with no arguments 
};
//Global
Button Prev(Previous_Track);
Button Play(Play_Pause);
Button Next(Next_Track);

void setupPin(Button& b){ pinMode(b.pin, INPUT_PULLUP);}
void led_blink(unsigned ms =40){ 
  digitalWrite(LED_Light, HIGH); 
  delay(ms); 
  digitalWrite(LED_Light,LOW);
  }

void setup(){
  Serial.begin(115200);
  setupPin(Prev); 
  setupPin(Play); 
  setupPin(Next);

  pinMode(LED_Light,OUTPUT);
  digitalWrite(LED_Light,LOW);

  bleKeyboard.begin(); //output BT signal
}

void service(Button&b,const uint8_t* shortKey, const uint8_t* longKey = nullptr){ //parameter: button&b holds the pin number, shortKey = what media key to send the short press to like pause/play and longkey = what media key to send long press like volume
  int rawpin = digitalRead(b.pin);//press = low idle = high
  unsigned long present = millis();
    //Debounce(tap)
  if (rawpin != b.read) { 
    b.read = rawpin; 
    b.LastChanged = present; 
    }
  if ((present - b.LastChanged) > debounce_ms) {
    if (rawpin != b.Stabled) {
      b.Stabled = rawpin;

      //pressed or released
      if (rawpin == LOW) {                 // stable press
        b.isPressed = true;
        b.pressedAt = present;
        b.isActive = false;         
        digitalWrite(LED_Light, HIGH);  // visual feedback
      } else if (b.isPressed) {         // stable release
        // If it never became a long-press, send the short action
        if (!b.isActive && shortKey && bleKeyboard.isConnected()) {
          bleKeyboard.write(shortKey);  // library sends press+release
          led_blink();                      //flash
        }
        b.isPressed = false;
        b.isActive = false;
        digitalWrite(LED_Light, LOW);
      }
    }
  }

  //Long-press 
  if (b.isPressed && !b.isActive && longKey && (present - b.pressedAt) >= holdpress_ms) {
    b.isActive = true;
    b.LastRepeated = 0;    // allow immediate first repeat
    led_blink(80);           //longer blink
  }

  // Long-press repeat loop volume
  if (b.isActive && longKey && bleKeyboard.isConnected()) {
    if (present - b.LastRepeated >= repeat_ms) {
      bleKeyboard.write(longKey);  
      b.LastRepeated = present;
    }
  }
}
void loop(){
service(Play, KEY_MEDIA_PLAY_PAUSE);                                // GPIO19
service(Next, KEY_MEDIA_NEXT_TRACK,     KEY_MEDIA_VOLUME_UP);       // GPIO21
service(Prev, KEY_MEDIA_PREVIOUS_TRACK, KEY_MEDIA_VOLUME_DOWN);     // GPIO18
}