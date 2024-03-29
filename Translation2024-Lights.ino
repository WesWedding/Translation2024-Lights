// Leave the next line commented out unless you are developing on a local environment, not using the final LED string.
// #define DEV_ENV

#include <Wire.h>
#include <PolledTimeout.h>

const int16_t I2C_LIGHT_ADDR = 0x2C;
const int16_t I2C_TOUCH_ADDR = 0x8C;
#define SDA_PIN 4
#define SCL_PIN 5

#include <Adafruit_NeoPixel.h>
#define LED_PIN    12
#if defined(DEV_ENV)
  #define LED_COUNT  16
#else
  #define LED_COUNT 60
#endif

#define BRIGHTNESS 100
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


#include <TweenDuino.h>
using namespace TweenDuino;

// Define the "areas" on the strip that have specific animations.
#if defined(DEV_ENV)
  #define STRIP_SEG1_START 0
  #define STRIP_SEG1_END   5
  #define STRIP_SEG2_START 7
  #define STRIP_SEG2_END   12
#else
  #define STRIP_SEG1_START 0
  #define STRIP_SEG1_END   20
  #define STRIP_SEG2_START 49
  #define STRIP_SEG2_END   60
#endif


#include "StripSegments.h"
strip_segments stripSegments = {
  { STRIP_SEG1_START, STRIP_SEG1_END },
  { STRIP_SEG2_START, STRIP_SEG2_END },
};

#include "IdleAnim.h"
#include "TouchedAnim.h"
#include "ClearAnimation.h"
IdleAnim idleAnim(strip, stripSegments);
TouchedAnim touchedAnim(strip, stripSegments);
ClearAnimation clearAnim(strip, stripSegments);

float ledPosition = 1;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN, I2C_LIGHT_ADDR);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(74880);
  strip.begin(); 
  strip.show();
  strip.setBrightness(BRIGHTNESS);
}


// Variables relevant to the loop.  Nice to have them down here, nearer the logic they're used in.
bool stateChanged = false;
char touchState;
void (*doBehavior)(void) = doStage0Behavior;

void loop() {
  using periodic = esp8266::polledTimeout::periodicMs;
  static periodic nextPing(100);

  digitalWrite(LED_BUILTIN, HIGH);

  if (nextPing) {
    Wire.requestFrom(I2C_TOUCH_ADDR, 1);  // request a bytes from 
    // Serial.print("Requested: ");

    char c = '\0';
    // Consume available bytes, and only hold on to the most recent one.
    while (Wire.available()) {  // slave may send less than requested
      c = Wire.read();     // receive a byte as character
       // Serial.print(c);          // print the character
      digitalWrite(LED_BUILTIN, LOW);  // Flicker the light
    }
    // Serial.println();

    // React only to the most recently recieved state.
    stateChanged = c != touchState;
    touchState = c;
  }

  if (!stateChanged) {
    doBehavior();
    return;
  }

  switch(touchState) {
    case '0':
      touchedAnim.stop();
      clearAnim.stop();
      idleAnim.start();
      doBehavior = doStage0Behavior;
      break;
    case '1':
      idleAnim.stop();
      clearAnim.stop();
      touchedAnim.start();
      doBehavior = doStage1Behavior;
      break;
    case '2':
      idleAnim.stop();
      touchedAnim.stop();
      clearAnim.start();
      doBehavior = doStage2Behavior;
      break;
    case '3':
      idleAnim.stop();
      touchedAnim.stop();
      clearAnim.stop();
      break;
    default:
      Serial.println("Unrecongized state.");
      break;
  }
  stateChanged = false;
  ledPosition = 1;
  doBehavior();
}

void doStage0Behavior() {
  idleAnim.update();
}

void doStage1Behavior() {
  touchedAnim.update();
}

void doStage2Behavior() {
  clearAnim.update();
}
