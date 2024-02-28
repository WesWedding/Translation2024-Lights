#include "ClearAnimation.h"

ClearAnimation::ClearAnimation(Adafruit_NeoPixel &strip, strip_segments &segments): 
                              strip(strip), 
                              segments(segments), 
                              initialFlicker(), 
                              rumbleFlicker(), 
                              rumbleMove(), 
                              brightness(0), 
                              rumbleModification(0),
                              position(0) {
  initialFlicker.addTo(brightness, 0.8, 25, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);
  initialFlicker.addTo(brightness, 0.75, 25, TweenDuino::Tween::SINE, TweenDuino::Tween::INOUT);


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
  initialFlicker.restartFrom(millis());
}

void ClearAnimation::stop() {
  running = false;
}

void ClearAnimation::update() {
  if (!running) return;

  initialFlicker.update(millis());
  rumbleFlicker.update(millis());

  strip.clear();
  const float brightVal = brightness + rumbleModification;
  for (int i = segments.firstArea.first; i <= segments.secondArea.last; i++) {
    uint32_t color = strip.Color(100 * brightVal, 200 * brightVal, 103 * brightVal);
    strip.setPixelColor(i, strip.gamma32(color));
  }

  strip.show();

  if (initialFlicker.isComplete()) {
    initialFlicker.restartFrom(millis());
  }
}