#ifndef __INCLUDED_38BCBE9AE7A511E6AA6EA088B4D1658C
#define __INCLUDED_38BCBE9AE7A511E6AA6EA088B4D1658C

#include "RRawPointer.h"
#include <WString.h>
#include <Stream.h>

class RNullStream : public Stream
{
public:
  RNullStream();

  virtual
  ~RNullStream();

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
  R_DISABLE_COPY(RNullStream);
};

#endif // __INCLUDED_38BCBE9AE7A511E6AA6EA088B4D1658C
