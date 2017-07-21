#include "RBufferStream.h"

RBufferStream::RBufferStream()
  : mBuffer(NULL)
  , mMaxSize(0)
  , mPos(0)
{
}

int
RBufferStream::available()
{
  return static_cast<int>(mMaxSize - mPos);
}

int
RBufferStream::read()
{
  if(mPos < mMaxSize)
  {
    int result = static_cast<int>(mBuffer[mPos]);

    mPos++;

    return result;
  }

  return -1;
}

int
RBufferStream::peek()
{
  if(mPos < mMaxSize)
  {
    int result = static_cast<int>(mBuffer[mPos]);

    return result;
  }

  return -1;
}

void
RBufferStream::flush()
{
}

size_t
RBufferStream::write(uint8_t c)
{
  if(mPos < mMaxSize)
  {
    mBuffer[mPos] = c;

    mPos++;

    return 1;
  }

  return 0;
}

void
RBufferStream::reset()
{
  mPos = 0;
}
