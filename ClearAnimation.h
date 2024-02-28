#ifndef _H_CLEAR_ANIM
#define _H_CLEAR_ANIM

#include <Adafruit_NeoPixel.h>
#include <TweenDuino.h>
#include "StripSegments.h"

using namespace TweenDuino;
class ClearAnimation {
  public:
    ClearAnimation(Adafruit_NeoPixel&, strip_segments& segments);
    void start();
    void stop();
    void update();
  private:
    bool running;
    Adafruit_NeoPixel &strip;
    const strip_segments& segments;
    Timeline initialFlicker;
    Timeline rumbleFlicker;
    Timeline rumbleMove;
    float brightness;
    float rumbleModification;
    int position;
};

#endif