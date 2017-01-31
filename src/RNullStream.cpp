#include "RNullStream.h"

RNullStream::RNullStream()
{
}

RNullStream::~RNullStream()
{
}

int
RNullStream::available()
{
  return 0;
}

int
RNullStream::read()
{
  return -1;
}

int
RNullStream::peek()
{
  return -1;
}

void
RNullStream::flush()
{
}

size_t
RNullStream::write(uint8_t c)
{
  /* Null stream could write always */
  return 1;
}
