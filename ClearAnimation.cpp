#include "ClearAnimation.h"
#include <math.h>


#define BASELINE_MAG 80
#define COLOR1R_INIT BASELINE_MAG
#define COLOR1G_INIT BASELINE_MAG
#define COLOR1B_INIT BASELINE_MAG

#define COLOR2R_INIT BASELINE_MAG
#define COLOR2G_INIT BASELINE_MAG
#define COLOR2B_INIT BASELINE_MAG

#define COLOR1R 23.9
#define COLOR1G 31.2
#define COLOR1B 36.6

#define FIRST_RUMBLE_START 22698

#define SECOND_RUMBLE_START 34724

#define SOUND_DURATION 41216

ClearAnimation::ClearAnimation(Adafruit_NeoPixel &strip, strip_segments &segments): 
                              strip(strip), 
                              segments(segments),
                              splotch1RTl(),
                              splotch1GTl(),
                              splotch1BTl(),
                              splotch1{COLOR1R_INIT, COLOR1G_INIT, COLOR1B_INIT},
                              splotch2RTl(),
                              splotch2GTl(),
                              splotch2BTl(),
                              splotch2{COLOR2R_INIT, COLOR2G_INIT, COLOR2B_INIT},
                              blipEvensBrightness(0.0),
                              blipOddsBrightness(0.0),
                              blipEvens(),
                              blipOdds(),
                              thunderBrightness(1.0),
                              thunder(),
                              fadeBrightness(1.0),
                              fadeOut() {

  // Don't change anything initially
  splotch1RTl.addTo(splotch1[0], COLOR1R_INIT, 22806);
  splotch1GTl.addTo(splotch1[1], COLOR1G_INIT, 22806);
  splotch1BTl.addTo(splotch1[2], COLOR1B_INIT, 22806);

  splotch2RTl.addTo(splotch2[0], COLOR1R_INIT, 22806);
  splotch2GTl.addTo(splotch2[1], COLOR1G_INIT, 22806);
  splotch2BTl.addTo(splotch2[2], COLOR1B_INIT, 22806);

  // blue splotch roughly rgb:  23.9, 31.2, 36.6
  splotch1RTl.addTo(splotch1[0], 23.9 * 3, 5000);
  splotch1GTl.addTo(splotch1[1], 31.2 * 3, 5000);
  splotch1BTl.addTo(splotch1[2], 36.6 * 3, 5000);

  // yellow splotches roughly rgb: 62.4, 54.3, 33.7
  splotch2RTl.addTo(splotch2[0], 62.4 * 3, 5000);
  splotch2GTl.addTo(splotch2[1], 54.3 * 3, 5000);
  splotch2BTl.addTo(splotch2[2], 33.7 * 3, 5000);

  blipEvens.addTo(blipEvensBrightness, 1, 186); // Hold steady
  blipEvens.addTo(blipEvensBrightness, 1.75, 35);
  blipEvens.addTo(blipEvensBrightness, 1, 100);
  blipEvens.addTo(blipEvensBrightness, 1, 65); // Hold steady
  blipEvens.addTo(blipEvensBrightness, 1.75, 35);
  blipEvens.addTo(blipEvensBrightness, 1, 100);
  blipEvens.addTo(blipEvensBrightness, 1, 111); // Hold steady
  blipEvens.addTo(blipEvensBrightness, 1.75, 35);
  blipEvens.addTo(blipEvensBrightness, 1, 100);

  blipOdds.addTo(blipOddsBrightness, 1, 92); // Hold steady for an amount different than evens to appear random
  blipOdds.addTo(blipOddsBrightness, 1.75, 35);
  blipOdds.addTo(blipOddsBrightness, 1, 100);
  blipOdds.addTo(blipOddsBrightness, 1, 231); // Hold steady for an amount different than evens to appear random
  blipOdds.addTo(blipOddsBrightness, 1.75, 35);
  blipOdds.addTo(blipOddsBrightness, 1, 100);
  blipOdds.addTo(blipOddsBrightness, 1, 70); // Hold steady for an amount different than evens to appear random
  blipOdds.addTo(blipOddsBrightness, 1.75, 35);
  blipOdds.addTo(blipOddsBrightness, 1, 100);

  thunder.addTo(thunderBrightness, 1.0, FIRST_RUMBLE_START);  // Don't visually "thunder" for a while
  thunder.addTo(thunderBrightness, 1.5, 975);
  thunder.addTo(thunderBrightness, 1.0, 300);
  thunder.addTo(thunderBrightness, 1.0, SECOND_RUMBLE_START - 975 - 300 - FIRST_RUMBLE_START);
  thunder.addTo(thunderBrightness, 1.5, 1246);
  thunder.addTo(thunderBrightness, 1.25, 813);
  thunder.addTo(thunderBrightness, 2.0, 704);
  thunder.addTo(thunderBrightness, 2.0, 500);
  thunder.addTo(thunderBrightness, 1.0, 1000);

  const int fadeDuration = 1000;
  fadeOut.addTo(fadeBrightness, 1.0, SOUND_DURATION - fadeDuration);
  fadeOut.addTo(fadeBrightness, 0.0, fadeDuration);
}

void ClearAnimation::start() {
  running = true;
  splotch1[0] = COLOR1R_INIT;
  splotch1[1] = COLOR1G_INIT;
  splotch1[2] = COLOR1B_INIT;

  splotch2[0] = COLOR2R_INIT;
  splotch2[1] = COLOR2G_INIT;
  splotch2[2] = COLOR2B_INIT;

  splotch1RTl.restartFrom(millis());
  splotch1GTl.restartFrom(millis());
  splotch1BTl.restartFrom(millis());

  splotch2RTl.restartFrom(millis());
  splotch2GTl.restartFrom(millis());
  splotch2BTl.restartFrom(millis());


  blipEvensBrightness = 1.0;
  blipOddsBrightness = 1.0;
  blipEvens.restartFrom(millis());
  blipOdds.restartFrom(millis());

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

  splotch1RTl.update(millis());
  splotch1GTl.update(millis());
  splotch1BTl.update(millis());

  splotch2RTl.update(millis());
  splotch2GTl.update(millis());
  splotch2BTl.update(millis());


  blipEvens.update(millis());
  blipOdds.update(millis());

  thunder.update(millis());

  fadeOut.update(millis());

  strip.clear();

  // Add "splotches" of color, repeating every 10 pixels.
  // 0 = blue, 1= white, 2 = yellow
  const short int colorLookup[10] = {0, 0, 0, 0, 1, 2, 2, 2, 2, 1};
  const uint16_t numLeds = strip.numPixels();

  for (int i = 0; i <= numLeds; i++) {
    const short int currentSpot = i % 10; // 10 is the size of colorLookup array

    // Grab the brightness from either the evens or odds depending on... well, oddness or evenness.
    const float &blipBrightness = (i % 2 == 0) ? blipEvensBrightness : blipOddsBrightness;

    uint32_t color = 4294967295;
    if (colorLookup[currentSpot] == 0) {
      color = strip.Color(
        min(254.0f, splotch1[0] * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, splotch1[1] * blipBrightness * thunderBrightness * fadeBrightness),
        min(254.0f, splotch1[2] * blipBrightness * thunderBrightness * fadeBrightness)
      );
    } else if (colorLookup[currentSpot] == 1) {
      color = strip.Color(
        min(254.0f, COLOR1R_INIT  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, COLOR1G_INIT  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, COLOR1B_INIT  * blipBrightness * thunderBrightness * fadeBrightness)
      );
    } else if (colorLookup[currentSpot] == 2 ) {
      color = strip.Color(
        min(254.0f, splotch2[0]  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, splotch2[1]  * blipBrightness * thunderBrightness * fadeBrightness), 
        min(254.0f, splotch2[2]  * blipBrightness * thunderBrightness * fadeBrightness)
      );
    }
    strip.setPixelColor(i, strip.gamma32(color));
  }

  strip.show();

  if (blipEvens.isComplete()) {
    blipEvens.restartFrom(millis());
  }
  
  if (blipOdds.isComplete()) {
    blipOdds.restartFrom(millis());
  }
}