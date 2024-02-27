#include <Wire.h>
#include <PolledTimeout.h>

const int16_t I2C_LIGHT_ADDR = 0x2C;
const int16_t I2C_TOUCH_ADDR = 0x8C;
#define SDA_PIN 4
#define SCL_PIN 5

#include <Adafruit_NeoPixel.h>
#define LED_PIN     12
#define LED_COUNT  16
#define BRIGHTNESS 50
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);


#include <TweenDuino.h>
using namespace TweenDuino;

Timeline state1;
Timeline state2;
Timeline state3;

float ledPosition = 1;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN, I2C_LIGHT_ADDR);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(74880);
  strip.begin(); 
  strip.show();
  strip.setBrightness(BRIGHTNESS);

  state1.addTo(ledPosition, LED_COUNT, 3000);
  state2.addTo(ledPosition, LED_COUNT, 10000);
  state3.addTo(ledPosition, LED_COUNT, 20000);
}


// Variables relevant to the loop.  Nice to have them down here, nearer the logic they're used in.
bool stateChanged = false;
char touchState;
Timeline *currentTl = &state1;
void (*doBehavior)(void) = doStage0Behavior;

void loop() {
  unsigned long int now = millis();
  currentTl->update(now);
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

  Serial.print("New state: ");  Serial.print(touchState);  Serial.println();

  switch(touchState) {
    case '0':
      currentTl = &state1;
      doBehavior = doStage0Behavior;
      break;
    case '1':
      currentTl = &state2;
      doBehavior = doStage1Behavior;
      break;
    case '2':
      currentTl = &state3;
      doBehavior = doStage2Behavior;
      break;
    default:
      Serial.println("Unrecongized state.");
      break;
  }
  stateChanged = false;
  ledPosition = 1;
  currentTl->restartFrom(now);
  doBehavior();
}

void doStage0Behavior() {
  strip.clear();
  strip.setPixelColor(ledPosition, strip.Color(200, 200, 200));
  strip.show();
}

void doStage1Behavior() {
  strip.clear();
  strip.setPixelColor(ledPosition, strip.Color(200, 200, 200));
  strip.show();
}

void doStage2Behavior() {
  strip.clear();
  strip.setPixelColor(ledPosition, strip.Color(200, 200, 200));
  strip.show();
}

