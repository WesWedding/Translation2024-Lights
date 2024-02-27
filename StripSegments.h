#ifndef _H_STRIP_SEGMENTS_
#define _H_STRIP_SEGMENTS_

struct Segment {
  short int first;
  short int last;
};

struct strip_segments {
  Segment firstArea;
  Segment secondArea;
};

#endif