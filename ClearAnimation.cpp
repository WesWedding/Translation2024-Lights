#include "ClearAnimation.h"

#define COLOR1R_INIT 255
#define COLOR1G_INIT 255
#define COLOR1B_INIT 255

#define COLOR2R_INIT 255
#define COLOR2G_INIT 255
#define COLOR2B_INIT 255

#define COLOR1R 23.9
#define COLOR1G 31.2
#define COLOR1B 36.6

ClearAnimation::ClearAnimation(Adafruit_NeoPixel &strip, strip_segments &segments): 
                              strip(strip), 
                              segments(segments),
                              initialFlicker(), 
                              rumbleFlicker(), 
                              rumbleMove(), 
                              brightness(0), 
                              rumbleModification(0),
                              splotch1RTl(),
                              splotch1GTl(),
                              splotch1BTl(),
                              splotch1{COLOR1R_INIT, COLOR1G_INIT, COLOR1B_INIT},
                              splotch2RTl(),
                              splotch2GTl(),
                              splotch2BTl(),
                              splotch2{COLOR2R_INIT, COLOR2G_INIT, COLOR2B_INIT},
                              position(0) {
  initialFlicker.addTo(brightness, 0.8, 25, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
  initialFlicker.addTo(brightness, 0.75, 25, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);


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

  // flat till 4395, 4443 peak, 4559 peak, 4717 low, peak 5659, 6115 peak, 6414 peak, 6759 peak, 6869 peak, 7195 low

  rumbleFlicker.addTo(rumbleModification, 0, 4395); // 4395 nothing
  rumbleFlicker.addTo(rumbleModification, 0.05, 48);  //4443
  rumbleFlicker.addTo(rumbleModification, 0.1, 116);  // 4559
  rumbleFlicker.addTo(rumbleModification, -0.05, 158);  // 4717 low
  rumbleFlicker.addTo(rumbleModification, 0.08, 942);  // 5659
  rumbleFlicker.addTo(rumbleModification, 0.0, 456);  // 6115
  rumbleFlicker.addTo(rumbleModification, 0.05, 299);  // 6414
  rumbleFlicker.addTo(rumbleModification, 0.00, 345);  // 6759
  rumbleFlicker.addTo(rumbleModification, 0.2, 110);  // 6869
  rumbleFlicker.addTo(rumbleModification, -0.05, 326);  // 7195 low
}

void ClearAnimation::start() {
  running = true;
  splotch1[0] = COLOR1R_INIT;
  splotch1[1] = COLOR1G_INIT;
  splotch1[2] = COLOR1B_INIT;

  splotch2[0] = COLOR2R_INIT;
  splotch2[1] = COLOR2G_INIT;
  splotch2[2] = COLOR2B_INIT;

  initialFlicker.restartFrom(millis());
  splotch1RTl.restartFrom(millis());
  splotch1GTl.restartFrom(millis());
  splotch1BTl.restartFrom(millis());

  splotch2RTl.restartFrom(millis());
  splotch2GTl.restartFrom(millis());
  splotch2BTl.restartFrom(millis());
}

void ClearAnimation::stop() {
  running = false;
}

void ClearAnimation::update() {
  if (!running) return;

  initialFlicker.update(millis());
  rumbleFlicker.update(millis());
  splotch1RTl.update(millis());
  splotch1GTl.update(millis());
  splotch1BTl.update(millis());

  splotch2RTl.update(millis());
  splotch2GTl.update(millis());
  splotch2BTl.update(millis());

  strip.clear();

  // Add "splotches" of color.  2 blue, 3 white, 2 yellow, 3 white, then repeat.
  // 0 = blue, 1= white, 2 = yellow
  const short int colorLookup[10] = {0, 0, 0, 0, 1, 2, 2, 2,2, 1};
  const uint32_t color0 = strip.Color(splotch1[0], splotch1[1], splotch1[2]);
  const uint32_t color1 = strip.Color(255, 255, 255);
  const uint32_t color2 = strip.Color(splotch2[0], splotch2[1], splotch2[2]);

  const float brightVal = brightness + rumbleModification;
  const uint16_t numLeds = strip.numPixels();
  for (int i = 0; i <= numLeds; i++) {
    const short int currentSpot = i % 10; // 10 is the size of colorLookup array
    uint32_t color = color1;

    if (colorLookup[currentSpot] == 0) {
      color = color0;
    } else if (colorLookup[currentSpot] == 1) {
      color = color1;
    } else if (colorLookup[currentSpot] == 2 ) {
      color = color2;
    }
    strip.setPixelColor(i, strip.gamma32(color));
  }

  strip.show();

  if (initialFlicker.isComplete()) {
    initialFlicker.restartFrom(millis());
  }
}