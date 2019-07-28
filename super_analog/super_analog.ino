/*
  Super Blink

  Project to fade multiple LEDs defined by 
  the PIN_STATE struct and the pins array
*/

typedef enum MODE{FADE, COOL_DOWN} Mode;

// Structure to hold the pin information and current state
typedef struct PIN_STATE {
  byte pin;                           // board pin number to control
  byte brightness;                    // led brightness (0 - 255)
  unsigned short fade_duration;       // duration (ms) between fade steps
  unsigned short cool_down_duration;  // duration (ms) to "cool down" when led is off
  Mode mode;                          // LED state in FADE or COOL_DOWN mode
  unsigned long target;               // target MS to update pin mode/status
  short fade_inc;                     // direction for fade (1 = UP, -1 DOWN)
} PinState;

// number of pins to configure
const unsigned int PIN_COUNT = 3;

// intial pin configuration
PinState pins[PIN_COUNT] =
{
  {11, 0, 100, 5000, FADE, 0, 1},
  {10, 0, 40, 2000, FADE, 0, 1},
  {9, 255, 100, 7500, FADE, 0, 1}
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
    analogWrite(pins[i].pin, pins[i].brightness);

    if (pins[i].target <= current) {
      if (pins[i].mode == FADE) {
        pins[i].target = current + pins[i].fade_duration;

        if (pins[i].brightness == 255) {
          pins[i].fade_inc = -1;
          pins[i].brightness = pins[i].brightness + pins[i].fade_inc;
        } else if (pins[i].brightness == 0) {
          pins[i].mode = COOL_DOWN;
          pins[i].target = current + pins[i].cool_down_duration;
          pins[i].fade_inc = 1;
        } else {
          pins[i].brightness = pins[i].brightness + pins[i].fade_inc;
        }
      } else if (pins[i].mode == COOL_DOWN) {
          pins[i].mode = FADE;
          pins[i].brightness = pins[i].brightness + pins[i].fade_inc;
      }
    }
  }
  delay(20);
}
