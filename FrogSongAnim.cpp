#include "FrogSongAnim.h"
#include "Arduino.h"

#define BLUE_FROG_R 23.9
#define BLUE_FROG_G 31.2
#define BLUE_FROG_B 66.6

#define YELLOW_FROG_R 72.4
#define YELLOW_FROG_G 64.3
#define YELLOW_FROG_B 33.7

FrogSongAnim::FrogSongAnim(short int r, short int g, short int b, float (&frog1RGB)[3], float (&frog2RGB)[3]):
                          currentFrog1Song(NONE),
                          baselineR(r), 
                          baselineG(g), 
                          baselineB(b),
                          frog1RGB(frog1RGB),
                          frog2RGB(frog2RGB),
                          frog1Song1R(),
                          frog1Song1G(),
                          frog1Song1B(),
                          frog1Song2R(),
                          frog1Song2G(),
                          frog1Song2B(),
                          frog1Song3R(),
                          frog1Song3G(),
                          frog1Song3B(),
                          frog2Song1R(),
                          frog2Song1G(),
                          frog2Song1B(),
                          frog2Song2R(),
                          frog2Song2G(),
                          frog2Song2B(),
                          frog2Song3R(),
                          frog2Song3G(),
                          frog2Song3B() {

  frog1Song1R.addTo(frog1RGB[0], BLUE_FROG_R * 3, 1000, Tween::SINE, Tween::INOUT);
  frog1Song1G.addTo(frog1RGB[1], BLUE_FROG_G * 3, 1000, Tween::SINE, Tween::INOUT);
  frog1Song1B.addTo(frog1RGB[2], BLUE_FROG_B * 3, 1000, Tween::SINE, Tween::INOUT);
  // Total song duration: 8700ms (minus ramp up/down).
  frog1Song1R.addTo(frog1RGB[0], BLUE_FROG_R * 3, 6700);
  frog1Song1G.addTo(frog1RGB[1], BLUE_FROG_G * 3, 6700);
  frog1Song1B.addTo(frog1RGB[2], BLUE_FROG_B * 3, 6700);
  frog1Song1R.addTo(frog1RGB[0], baselineR, 1000, Tween::SINE, Tween::INOUT);
  frog1Song1G.addTo(frog1RGB[1], baselineG, 1000, Tween::SINE, Tween::INOUT);
  frog1Song1B.addTo(frog1RGB[2], baselineB, 1000, Tween::SINE, Tween::INOUT);

  frog1Song2R.addTo(frog1RGB[0], BLUE_FROG_R * 3, 1000, Tween::SINE, Tween::INOUT);
  frog1Song2G.addTo(frog1RGB[1], BLUE_FROG_G * 3, 1000, Tween::SINE, Tween::INOUT);
  frog1Song2B.addTo(frog1RGB[2], BLUE_FROG_B * 3, 1000, Tween::SINE, Tween::INOUT);
  // Total song duration: 7804ms (minus ramp up/down).
  frog1Song2R.addTo(frog1RGB[0], BLUE_FROG_R * 3, 5804);
  frog1Song2G.addTo(frog1RGB[1], BLUE_FROG_G * 3, 5804);
  frog1Song2B.addTo(frog1RGB[2], BLUE_FROG_B * 3, 5804);
  frog1Song2R.addTo(frog1RGB[0], baselineR, 1000, Tween::SINE, Tween::INOUT);
  frog1Song2G.addTo(frog1RGB[1], baselineG, 1000, Tween::SINE, Tween::INOUT);
  frog1Song2B.addTo(frog1RGB[2], baselineB, 1000, Tween::SINE, Tween::INOUT);

  frog1Song3R.addTo(frog1RGB[0], BLUE_FROG_R * 3, 1000, Tween::SINE, Tween::INOUT);
  frog1Song3G.addTo(frog1RGB[1], BLUE_FROG_G * 3, 1000, Tween::SINE, Tween::INOUT);
  frog1Song3B.addTo(frog1RGB[2], BLUE_FROG_B * 3, 1000, Tween::SINE, Tween::INOUT);
  // Total song duration: 4087ms (minus ramp up/down).
  frog1Song3R.addTo(frog1RGB[0], BLUE_FROG_R * 3, 3087);
  frog1Song3G.addTo(frog1RGB[1], BLUE_FROG_G * 3, 3087);
  frog1Song3B.addTo(frog1RGB[2], BLUE_FROG_B * 3, 3087);
  frog1Song3R.addTo(frog1RGB[0], baselineR, 1000, Tween::SINE, Tween::INOUT);
  frog1Song3G.addTo(frog1RGB[1], baselineG, 1000, Tween::SINE, Tween::INOUT);
  frog1Song3B.addTo(frog1RGB[2], baselineB, 1000, Tween::SINE, Tween::INOUT);

  // Frog 2!

  frog2Song1R.addTo(frog2RGB[0], YELLOW_FROG_R * 3, 1000, Tween::SINE, Tween::INOUT);
  frog2Song1G.addTo(frog2RGB[1], YELLOW_FROG_G * 3, 1000, Tween::SINE, Tween::INOUT);
  frog2Song1B.addTo(frog2RGB[2], YELLOW_FROG_B * 3, 1000, Tween::SINE, Tween::INOUT);
  // Total song duration: 2141ms (minus ramp up/down).
  frog2Song1R.addTo(frog2RGB[0], YELLOW_FROG_R * 3, 1741);
  frog2Song1G.addTo(frog2RGB[1], YELLOW_FROG_G * 3, 1741);
  frog2Song1B.addTo(frog2RGB[2], YELLOW_FROG_B * 3, 1741);
  frog2Song1R.addTo(frog2RGB[0], baselineR, 300, Tween::SINE, Tween::INOUT);
  frog2Song1G.addTo(frog2RGB[1], baselineG, 300, Tween::SINE, Tween::INOUT);
  frog2Song1B.addTo(frog2RGB[2], baselineB, 300, Tween::SINE, Tween::INOUT);

  frog2Song2R.addTo(frog2RGB[0], YELLOW_FROG_R * 3, 500, Tween::SINE, Tween::INOUT);
  frog2Song2G.addTo(frog2RGB[1], YELLOW_FROG_G * 3, 500, Tween::SINE, Tween::INOUT);
  frog2Song2B.addTo(frog2RGB[2], YELLOW_FROG_B * 3, 500, Tween::SINE, Tween::INOUT);
  // Total song duration: 7425ms (minus ramp up/down).
  frog2Song2R.addTo(frog2RGB[0], YELLOW_FROG_R * 3, 6825);
  frog2Song2G.addTo(frog2RGB[1], YELLOW_FROG_G * 3, 6825);
  frog2Song2B.addTo(frog2RGB[2], YELLOW_FROG_B * 3, 6825);
  frog2Song2R.addTo(frog2RGB[0], baselineR, 1000, Tween::SINE, Tween::INOUT);
  frog2Song2G.addTo(frog2RGB[1], baselineG, 1000, Tween::SINE, Tween::INOUT);
  frog2Song2B.addTo(frog2RGB[2], baselineB, 1000, Tween::SINE, Tween::INOUT);

  frog2Song3R.addTo(frog2RGB[0], YELLOW_FROG_R * 3, 500, Tween::SINE, Tween::INOUT);
  frog2Song3G.addTo(frog2RGB[1], YELLOW_FROG_G * 3, 500, Tween::SINE, Tween::INOUT);
  frog2Song3B.addTo(frog2RGB[2], YELLOW_FROG_B * 3, 500, Tween::SINE, Tween::INOUT);
  // Total song duration: 5352ms (minus ramp up/down).
  frog2Song3R.addTo(frog2RGB[0], YELLOW_FROG_R * 3, 4252);
  frog2Song3G.addTo(frog2RGB[1], YELLOW_FROG_G * 3, 4252);
  frog2Song3B.addTo(frog2RGB[2], YELLOW_FROG_B * 3, 4252);
  frog2Song3R.addTo(frog2RGB[0], baselineR, 1000, Tween::SINE, Tween::INOUT);
  frog2Song3G.addTo(frog2RGB[1], baselineG, 1000, Tween::SINE, Tween::INOUT);
  frog2Song3B.addTo(frog2RGB[2], baselineB, 1000, Tween::SINE, Tween::INOUT);
  
}

void FrogSongAnim::startFrog1Song1() {
  Serial.println("starting 1-1");
  currentFrog1Song = FIRST;
  frog1Song1R.restartFrom(millis());
  frog1Song1G.restartFrom(millis());
  frog1Song1B.restartFrom(millis());
}

void FrogSongAnim::startFrog1Song2() {
  Serial.println("starting 1-2");
  currentFrog1Song = SECOND;
  frog1Song2R.restartFrom(millis());  
  frog1Song2G.restartFrom(millis());  
  frog1Song2B.restartFrom(millis());  
}

void FrogSongAnim::startFrog1Song3() {
  Serial.println("starting 1-3");
  currentFrog1Song = THIRD;
  frog1Song3R.restartFrom(millis());  
  frog1Song3G.restartFrom(millis());
  frog1Song3B.restartFrom(millis());  
}

void FrogSongAnim::startFrog2Song1() {
  Serial.println("starting 2-1");
  currentFrog2Song = F2_SONG1;
  frog2Song1R.restartFrom(millis());
  frog2Song1G.restartFrom(millis());
  frog2Song1B.restartFrom(millis());
}

void FrogSongAnim::startFrog2Song2() {
  Serial.println("starting 2-2");
  currentFrog2Song = F2_SONG2;
  frog2Song2R.restartFrom(millis());
  frog2Song2G.restartFrom(millis());
  frog2Song2B.restartFrom(millis());
}

void FrogSongAnim::startFrog2Song3() {
  Serial.println("starting 2-3");
  currentFrog2Song = F2_SONG3;
  frog2Song3R.restartFrom(millis());
  frog2Song3G.restartFrom(millis());
  frog2Song3B.restartFrom(millis());
}

void FrogSongAnim::reset() {
  currentFrog1Song = NONE;
  currentFrog2Song = NONE;
}

Song FrogSongAnim::getCurrentFrog1Song() {
  return currentFrog1Song;
}

void FrogSongAnim::update() {
  updateFrog1();
  updateFrog2();
}

void FrogSongAnim::updateFrog1() {
  if (currentFrog1Song == NONE) {
    return;
  }

  Timeline *RTimeline = NULL;
  Timeline *GTimeline = NULL;
  Timeline *BTimeline = NULL;

  switch (currentFrog1Song) {
    case FIRST:
      RTimeline = &frog1Song1R;
      GTimeline = &frog1Song1G;
      BTimeline = &frog1Song1B;
      break;
    case SECOND:
      RTimeline = &frog1Song2R;
      GTimeline = &frog1Song2G;
      BTimeline = &frog1Song2B;  
      break;
    case THIRD:
      RTimeline = &frog1Song3R;
      GTimeline = &frog1Song3G;
      BTimeline = &frog1Song3B;
      break;
    case NONE:
    default:
      break;
  }
  if (RTimeline == NULL || GTimeline == NULL || BTimeline == NULL ) {
    return;
  }

  const unsigned long now = millis();
  RTimeline->update(now);
  GTimeline->update(now);
  BTimeline->update(now);

  if (RTimeline->isComplete() && GTimeline->isComplete() && BTimeline->isComplete()) {
    Serial.println("Frog 1 Completed.");
    currentFrog1Song = NONE;
  }
}

void FrogSongAnim::updateFrog2() {
  if (currentFrog2Song == NONE) {
    return;
  }

  Timeline *RTimeline = NULL;
  Timeline *GTimeline = NULL;
  Timeline *BTimeline = NULL;

  switch (currentFrog2Song) {
    case F2_SONG1:
      RTimeline = &frog2Song1R;
      GTimeline = &frog2Song1G;
      BTimeline = &frog2Song1B;
      break;
    case F2_SONG2:
      RTimeline = &frog2Song2R;
      GTimeline = &frog2Song2G;
      BTimeline = &frog2Song2B;  
      break;
    case F2_SONG3:
      RTimeline = &frog2Song3R;
      GTimeline = &frog2Song3G;
      BTimeline = &frog2Song3B;
      break;
    case NONE:
    default:
      break;
  }
  if (RTimeline == NULL || GTimeline == NULL || BTimeline == NULL ) {
    return;
  }

  const unsigned long now = millis();
  RTimeline->update(now);
  GTimeline->update(now);
  BTimeline->update(now);

  if (RTimeline->isComplete() && GTimeline->isComplete() && BTimeline->isComplete()) {
    Serial.println("Frog 2 Completed.");
    currentFrog2Song = NONE;
  }
}