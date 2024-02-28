#include "TouchedAnim.h"

TouchedAnim::TouchedAnim(Adafruit_NeoPixel &strip, strip_segments &segments): strip(strip), segments(segments), fadeTl(), moveTl(), brightness(0), position(0) {
  fadeTl.addTo(brightness, 1.0, 23, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
  fadeTl.addTo(brightness, 0.0, 23, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
}

void TouchedAnim::start() {
  running = true;
  fadeTl.restartFrom(millis());
}

void TouchedAnim::stop() {
  running = false;
}

void TouchedAnim::update() {
  if (!running) return;

  fadeTl.update(millis());

  strip.clear();
  for (int i = segments.firstArea.first; i <= segments.secondArea.last; i++) {
    uint32_t color = strip.Color(100 * brightness, 200 * brightness, 103 * brightness);
    strip.setPixelColor(i, strip.gamma32(color));
  }

  strip.show();

  if (fadeTl.isComplete()) {
    fadeTl.restartFrom(millis());
  }
}