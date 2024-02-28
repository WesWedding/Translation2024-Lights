#ifndef _H_TOUCHED_ANIM
#define _H_TOUCHED_ANIM

// Buzzing vibration sound effect that buzzes at about 26 millisecs per crest

#include <Adafruit_NeoPixel.h>
#include <TweenDuino.h>
#include "StripSegments.h"

using namespace TweenDuino;
class TouchedAnim {
  public:
    TouchedAnim(Adafruit_NeoPixel&, strip_segments& segments);
    void start();
    void stop();
    void update();
  private:
    bool running;
    Adafruit_NeoPixel &strip;
    const strip_segments& segments;
    Timeline fadeTl;
    Timeline moveTl;
    float brightness;
    int position;
};

#endif