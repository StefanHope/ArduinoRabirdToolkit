#ifndef __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C
#define __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C

#include <pt.h>

class RCoRoutineRunner
{
public:
  RCoRoutineRunner();
  virtual
  ~RCoRoutineRunner();

  virtual char
  run();

public:
  struct pt mPt;
};

#endif // __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C
