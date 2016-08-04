#ifndef __INCLUDED_1145BD925A1411E69BAF00F1F38F93EF
#define __INCLUDED_1145BD925A1411E69BAF00F1F38F93EF

#include "RRawPointer.h"
#include <WString.h>
#include <Stream.h>

class RStringStream : protected Stream
{
public:
  RStringStream(String *strPtr);

  virtual
  ~RStringStream();

  int
  available();

  int
  read();

  int
  peek();

  void
  flush();

  // Print methods
  size_t
  write(uint8_t c);

private:
  RRawPointer<String> mStrPtr;
};

#endif // __INCLUDED_1145BD925A1411E69BAF00F1F38F93EF
