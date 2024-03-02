#include "TouchedAnim.h"

#define LOWEST_BRIGHTNESS  0.4

TouchedAnim::TouchedAnim(Adafruit_NeoPixel &strip, strip_segments &segments): strip(strip), segments(segments), brightnessTl(), moveTl(), brightness(LOWEST_BRIGHTNESS), position(segments.firstArea.first) {

// 463ms length from crest to crest
  brightnessTl.addTo(brightness, 1.0, 375, TweenDuino::Tween::SINE, TweenDuino::Tween::IN);
  brightnessTl.addTo(brightness, LOWEST_BRIGHTNESS, 88, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
    
  moveTl.addTo(position, segments.secondArea.last, 375, TweenDuino::Tween::SINE, TweenDuino::Tween::IN);
  moveTl.addTo(position, segments.secondArea.last, 88);  // Stay full during fade out.
}

void TouchedAnim::start() {
  running = true;
  brightness = LOWEST_BRIGHTNESS;
  position = segments.firstArea.first;
  brightnessTl.restartFrom(millis());
  moveTl.restartFrom(millis());
}

void TouchedAnim::stop() {
  running = false;
}

void TouchedAnim::update() {
  if (!running) return;

  brightnessTl.update(millis());
  moveTl.update(millis());

  strip.clear();

  for (int i = segments.firstArea.first; i < segments.secondArea.last; i++) {
    const float magnitude = (i <= position) ? brightness : LOWEST_BRIGHTNESS;
    uint32_t color = strip.Color(255 * magnitude, 255 * magnitude, 255 * magnitude);
    strip.setPixelColor(i, strip.gamma32(color));
  }

  strip.show();

  if (brightnessTl.isComplete()) {
    brightnessTl.restartFrom(millis());
  }
  if (moveTl.isComplete()) {
    position = segments.firstArea.first;
    moveTl.restartFrom(millis());
  }
}