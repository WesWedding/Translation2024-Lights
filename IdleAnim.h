#ifndef _H_IDLE_ANIM
#define _H_IDLE_ANIM


#include <Adafruit_NeoPixel.h>
#include <TweenDuino.h>
#include "StripSegments.h"

using namespace TweenDuino;
class IdleAnim {
  public:
    IdleAnim(Adafruit_NeoPixel&, strip_segments& segments);
    void start();
    void stop();
    void update();
  private:
    bool running;
    Adafruit_NeoPixel &strip;
    const strip_segments& segments;
    Timeline fadeTl;
    float brightness;
};

#endif