#include "TweenDuino.h"

using namespace TweenDuino;

enum Song {
  FIRST,
  SECOND,
  THIRD,
  F2_SONG1,
  F2_SONG2,
  F2_SONG3,
  NONE
};

class FrogSongAnim {
  public:
    FrogSongAnim(short int r, short int g, short int b, float (&frog1RGB)[3], float (&frog2RGB)[3]);
    void update();

    void startFrog1Song1();
    void startFrog1Song2();
    void startFrog1Song3();
    void startFrog2Song1();
    void startFrog2Song2();
    void startFrog2Song3();

    Song getCurrentFrog1Song();
  private:
    
    void updateFrog1();
    void updateFrog2();

    Song currentFrog1Song;
    Song currentFrog2Song;

    short int baselineR;
    short int baselineG;
    short int baselineB;

    float (&frog1RGB)[3];
    float (&frog2RGB)[3];

    Timeline frog1Song1R;
    Timeline frog1Song1G;
    Timeline frog1Song1B;

    Timeline frog1Song2R;
    Timeline frog1Song2G;
    Timeline frog1Song2B;

    Timeline frog1Song3R;
    Timeline frog1Song3G;
    Timeline frog1Song3B;

    Timeline frog2Song1R;
    Timeline frog2Song1G;
    Timeline frog2Song1B;

    Timeline frog2Song2R;
    Timeline frog2Song2G;
    Timeline frog2Song2B;

    Timeline frog2Song3R;
    Timeline frog2Song3G;
    Timeline frog2Song3B;
};