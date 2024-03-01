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
    Timeline splotch1RTl;
    Timeline splotch1GTl;
    Timeline splotch1BTl;
    float splotch1[3];
    Timeline splotch2RTl;
    Timeline splotch2GTl;
    Timeline splotch2BTl;
    float splotch2[3];
};

#endif