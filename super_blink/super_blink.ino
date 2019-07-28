/*
  Super Blink

  Project to blink multiple LEDs at different frequencies defined by 
  the PIN_STATE struct and the pins array
*/

// Structure to hold the pin information and current state
typedef struct PIN_STATE {
  unsigned int pin;           // board pin number to control
  boolean state;              // pin state (true == on, false == off)
  unsigned int on_duration;   // time in millis to turn the pin on
  unsigned int off_duration;  // time in millis to turn the pin off
  unsigned long threshold;    // managed by loop() - sets the time for the next state check
} PinState;

// number of pins to configure
const unsigned int PIN_COUNT = 3;

// intial pin configuration
PinState pins[PIN_COUNT] =
{
  {13, false, 1000, 1000, 0},
  {12, false, 1000, 1200, 0},
  {2, false, 1000, 1100, 0}
};

// setup the configured pins
void setup() {
  for (int i = 0; i < PIN_COUNT; i++) {
    pinMode(pins[i].pin, OUTPUT);
  }
}

// update the state of the configured pins
void loop() {
  unsigned long current = millis();
  for (int i = 0; i < PIN_COUNT; i++) {
    if (pins[i].threshold <= current) {
      if (pins[i].state) {
        pins[i].threshold = current + pins[i].off_duration;
      } else {
        pins[i].threshold = current + pins[i].on_duration;
      }

      pins[i].state = !pins[i].state;
      digitalWrite(pins[i].pin, pins[i].state);
    }
  }
  delay(100);
}
