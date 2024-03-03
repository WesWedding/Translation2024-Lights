#include "ClearAnimation.h"
#include <math.h>


#define BASELINE_MAG 70
#define COLOR1R_INIT BASELINE_MAG
#define COLOR1G_INIT BASELINE_MAG
#define COLOR1B_INIT BASELINE_MAG

#define COLOR2R_INIT BASELINE_MAG
#define COLOR2G_INIT BASELINE_MAG
#define COLOR2B_INIT BASELINE_MAG

#define BLUE_FROG_R 23.9
#define BLUE_FROG_G 31.2
#define BLUE_FROG_B 36.6

#define YELLOW_FROG_R 62.4
#define YELLOW_FROG_G 54.3
#define YELLOW_FROG_B 33.7

#define FIRST_RUMBLE_START 22427

#define SECOND_RUMBLE_START 34724

#define SOUND_DURATION 41216

ClearAnimation::ClearAnimation(Adafruit_NeoPixel &strip, strip_segments &segments): 
                              strip(strip), 
                              segments(segments),
                              splotch1{COLOR1R_INIT, COLOR1G_INIT, COLOR1B_INIT},
                              splotch2{COLOR2R_INIT, COLOR2G_INIT, COLOR2B_INIT},
                              frogAnim(COLOR1R_INIT, COLOR1G_INIT, COLOR1B_INIT, splotch1, splotch2),
                              blipEvensBrightness(0.0),
                              blipOddsBrightness(0.0),
                              blipEvens(),
                              blipOdds(),
                              startOfAnim(0),
                              blipEvenLast(0),
                              blipOddLast(0),
                              blipEvenNext(0),
                              blipOddNext(0),
                              thunderBrightness(1.0),
                              thunder(),
                              fadeBrightness(1.0),
                              fadeOut(),
                              frog1Played{false, false, false},
                              frog2Played{false, false, false} {

  blipEvens.addTo(blipEvensBrightness, 1.75, 35, Tween::SINE, Tween::INOUT);
  blipEvens.addTo(blipEvensBrightness, 1, 100, Tween::SINE, Tween::INOUT);

  blipOdds.addTo(blipOddsBrightness, 1.75, 35, Tween::SINE, Tween::INOUT);
  blipOdds.addTo(blipOddsBrightness, 1, 100, Tween::SINE, Tween::INOUT);

  thunder.addTo(thunderBrightness, 1.0, FIRST_RUMBLE_START, Tween::SINE, Tween::INOUT);  // Don't visually "thunder" for a while
  thunder.addTo(thunderBrightness, 1.5, 200, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 1.0, 900, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 1.0, SECOND_RUMBLE_START - 200 - 900 - FIRST_RUMBLE_START, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 2.0, 646, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 1.5, 1413, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 2.0, 704, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 3.0, 500, Tween::SINE, Tween::INOUT);
  thunder.addTo(thunderBrightness, 1.0, 1000, Tween::SINE, Tween::INOUT);

  const int fadeDuration = 1000;
  fadeOut.addTo(fadeBrightness, 1.0, SOUND_DURATION - fadeDuration, Tween::SINE, Tween::INOUT);
  fadeOut.addTo(fadeBrightness, 0.0, fadeDuration, Tween::SINE, Tween::INOUT);
}

void ClearAnimation::start() {
  running = true;
  splotch1[0] = COLOR1R_INIT;
  splotch1[1] = COLOR1G_INIT;
  splotch1[2] = COLOR1B_INIT;

  splotch2[0] = COLOR2R_INIT;
  splotch2[1] = COLOR2G_INIT;
  splotch2[2] = COLOR2B_INIT;

  frogAnim.reset();

  startOfAnim = millis();

  frog1Played[0] = false;
  frog1Played[1] = false;
  frog1Played[2] = false;

  frog2Played[0] = false;
  frog2Played[1] = false;
  frog2Played[2] = false;

  blipEvensBrightness = 1.0;
  blipOddsBrightness = 1.0;
  blipEvenNext = millis() + random(50, 750);
  blipOddNext = millis() + random(50, 750);
  blipEvenLast = millis();
  blipOddLast = millis();

  thunderBrightness = 1.0;
  thunder.restartFrom(millis());

  fadeBrightness = 1.0;
  fadeOut.restartFrom(millis());
}

void ClearAnimation::stop() {
  running = false;
}

void ClearAnimation::update() {
  if (!running) return;

  const unsigned long now = millis();

  const unsigned long duration = now - startOfAnim;

  // Frog 1 Animation
  // Check in order of LARGEST duration first to keep conditionals simple
  if (duration >= 26375 && frog1Played[2] == false) {
    frog1Played[2] = true;
    frogAnim.startFrog1Song3();
  } else if (duration >= 11077 && frog1Played[1] == false) {
    frog1Played[1] = true;
    frogAnim.startFrog1Song2();
  } else if (duration >= 2278 && frog1Played[0] == false) {
    frog1Played[0] = true;
    frogAnim.startFrog1Song1();
  }

  // Frog 2 animations
  // Check in order of LARGEST duration first to keep conditionals simple
  if (duration >= 29814 && frog2Played[2] == false) {
    frog2Played[2] = true;
    frogAnim.startFrog2Song3();
  } else if (duration >= 16854 && frog2Played[1] == false) {
    frog2Played[1] = true;
    frogAnim.startFrog2Song2();
  } else if (duration >= 8678 && frog2Played[0] == false) {
    frog2Played[0] = true;
    frogAnim.startFrog2Song1();
  }

  frogAnim.update();

  if (now >= blipEvenNext) {
    blipEvens.restartFrom(now);
    blipEvenLast = now;
    blipEvenNext = now + random(50, 750);
  }
  if (now >= blipOddNext) {
    blipOdds.restartFrom(now);
    blipOddLast = now;
    blipOddNext = now + random(50, 750);
  }
  blipEvens.update(now);
  blipOdds.update(now);

  thunder.update(now);

  fadeOut.update(now);

  strip.clear();

  const uint16_t numLeds = strip.numPixels();

  for (int i = 0; i <= numLeds; i++) {
    // Grab the brightness from either the evens or odds depending on... well, oddness or evenness.
    const float &blipBrightness = (i % 2 == 0) ? blipEvensBrightness : blipOddsBrightness;

    uint32_t color = 4294967295;
    if (i >= segments.firstArea.first && i <= segments.firstArea.last) {
      color = strip.Color(
        min(254.0f, splotch1[0] * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, splotch1[1] * blipBrightness * thunderBrightness * fadeBrightness),
        min(254.0f, splotch1[2] * blipBrightness * thunderBrightness * fadeBrightness)
      );
    } else if (i >= segments.secondArea.first && i <= segments.secondArea.last) {
      color = strip.Color(
        min(254.0f, splotch2[0]  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, splotch2[1]  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, splotch2[2]  * blipBrightness * thunderBrightness * fadeBrightness)
      );
    } else {
      color = strip.Color(
        min(254.0f, COLOR1R_INIT  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, COLOR1G_INIT  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, COLOR1B_INIT  * blipBrightness * thunderBrightness * fadeBrightness)
      );
    }
    strip.setPixelColor(i, strip.gamma32(color));
  }
  strip.show();
}