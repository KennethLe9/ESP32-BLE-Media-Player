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
const unsigned long repeat_ms = 150;//for volume step speed

struct Button { //info that button needs: pin, if it is pressed, or hold, when is it press and released 
  int pin; //what pin is it located
  int Stabled; // debounced state High = idle and Low = Pressed
  int read; //to tell what is going on
  unsigned long LastChanged; //when changed happend
  unsigned long pressedAt; //time when the pressing began
  unsigned long LastRepeated;//for the volume feature 
  bool isPressed, isActive; //boolean to test what is going on

  Button(int gpio)
  : pin(gpio),Stable(HIGH),read(LOW),LastChanged(0),pressedAt(0),LastRepeated(0),isPressed(false),isActive(false){} //default setting
  Button() : Button(-1){}//Button with no arguments 
}
//Global
Button Prev(Previous_Track);
Button Play(Play_Pause);
Button Next(Next_Track);

void setupPin(Button& b){ pinMode(b.pin, INPUT_PULLUP);}
void led_blink(unsigned ms =40){ digitalWrite(LED_PIN, HIGH); delay(ms); digitalWrite(LED_PIN,LOW);}

void setup(){
  Serial.begin(115200);
  setupPin(Prev); setupPin(Play); setupPin(Next);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);
  bleKeyboard.begin(); //output BT signal
}