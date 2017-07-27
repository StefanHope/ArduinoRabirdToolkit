#include "RStringStream.h"

RStringStream::RStringStream(String *strPtr)
  : mStrPtr(strPtr)
{
}

RStringStream::~RStringStream()
{
}

int
RStringStream::available()
{
  return static_cast<int>(mStrPtr->length());
}

int
RStringStream::read()
{
  if(mStrPtr->length() > 0)
  {
    int result = static_cast<int>(static_cast<uint8_t>(mStrPtr->charAt(0)));

    mStrPtr->remove(0, 1);
    return result;
  }

  return -1;
}

int
RStringStream::peek()
{
  if(mStrPtr->length() > 0)
  {
    return static_cast<int>(static_cast<uint8_t>(mStrPtr->charAt(0)));
  }

  return -1;
}

void
RStringStream::flush()
{
}

// Print methods
size_t
RStringStream::write(uint8_t c)
{
  *mStrPtr += static_cast<char>(c);
  return 1;
}
