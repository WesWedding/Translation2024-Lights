#include "IdleAnim.h"

IdleAnim::IdleAnim(Adafruit_NeoPixel &strip, strip_segments &segments): strip(strip), segments(segments), fadeTl(), brightness(0) {
  fadeTl.addTo(brightness, 1.0, 1000, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
  fadeTl.addTo(brightness, 0.0, 1000, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
}

void IdleAnim::start() {
  running = true;
  fadeTl.restartFrom(millis());
}

void IdleAnim::stop() {
  running = false;
}

void IdleAnim::update() {
  if (!running) return;

  fadeTl.update(millis());

  strip.clear();
  for (int i = segments.firstArea.first; i <= segments.firstArea.last; i++) {
    uint32_t color = strip.Color(255 * brightness, 255  * brightness, 255 * brightness);
    strip.setPixelColor(i, strip.gamma32(color));
  }

  strip.show();

  if (fadeTl.isComplete()) {
    fadeTl.restartFrom(millis());
  }
}