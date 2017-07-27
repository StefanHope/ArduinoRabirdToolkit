#include "RBufferStream.h"

RBufferStream::RBufferStream()
  : mBuffer(NULL)
  , mMaxSize(0)
  , mReadPos(0)
  , mWritePos(0)
{
}

void
RBufferStream::setBuffer(uint8_t *buffer, rsize maxSize)
{
  mBuffer   = buffer;
  mMaxSize  = maxSize;
  mReadPos  = 0;
  mWritePos = 0;
}

int
RBufferStream::available()
{
  return static_cast<int>(mWritePos - mReadPos);
}

int
RBufferStream::read()
{
  if(mReadPos < mWritePos)
  {
    int result = static_cast<int>(mBuffer[mReadPos]);

    mReadPos++;

    return result;
  }

  return -1;
}

int
RBufferStream::peek()
{
  if(mReadPos < mWritePos)
  {
    int result = static_cast<int>(mBuffer[mReadPos]);

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
  if(mWritePos < mMaxSize)
  {
    mBuffer[mWritePos] = c;

    mWritePos++;

    return 1;
  }

  return 0;
}

void
RBufferStream::reset()
{
  mReadPos  = 0;
  mWritePos = 0;
}

rsize
RBufferStream::maxSize()
{
  return mMaxSize;
}
