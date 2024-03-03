#ifndef _H_CLEAR_ANIM
#define _H_CLEAR_ANIM

#include <Adafruit_NeoPixel.h>
#include <TweenDuino.h>
#include "StripSegments.h"
#include "FrogSongAnim.h"

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
    float splotch1[3];
    float splotch2[3];
    FrogSongAnim frogAnim;
    float blipEvensBrightness;
    float blipOddsBrightness;
    Timeline blipEvens;
    Timeline blipOdds;
    unsigned long startOfAnim;
    unsigned long blipEvenLast;
    unsigned long blipOddLast;
    unsigned long blipEvenNext;
    unsigned long blipOddNext;
    float thunderBrightness;
    Timeline thunder;
    float fadeBrightness;
    Timeline fadeOut;
    bool frog1Played[3];
    bool frog2Played[3];
};

#endif