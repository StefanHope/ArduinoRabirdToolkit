#ifndef __INCLUDED_FEEF21386D2511E7AA6EA088B4D1658C
#define __INCLUDED_FEEF21386D2511E7AA6EA088B4D1658C

#include <RGlobal.h>

class RBufferStream : public Stream
{
public:
  RBufferStream();

  void
  setBuffer(uint8_t *buffer, rsize maxSize);

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

  void
  reset();

  rsize
  maxSize();

  void
  setWritePos(rsize pos);

private:
  uint8_t *mBuffer;
  rsize    mMaxSize;
  rsize    mReadPos;
  rsize    mWritePos;

  R_DISABLE_COPY(RBufferStream)
};

#endif // __INCLUDED_FEEF21386D2511E7AA6EA088B4D1658C
