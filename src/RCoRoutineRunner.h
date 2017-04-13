#ifndef __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C
#define __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C

#include <pt/pt.h>

class RCoRoutineRunner
{
public:
  RCoRoutineRunner();
  virtual
  ~RCoRoutineRunner();

  virtual char
  run() = 0;

public:
  struct pt mPt;
};

#endif // __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C
