#include "RFlashStringRef.h"
#include <stdlib.h>
#include <avr/pgmspace.h>

RFlashStringRef::RFlashStringRef(const rfchar *flashStr)
  : mStr(flashStr)
  , mLength(0)
{
  if(NULL != flashStr)
  {
    mLength = strlen_P(reinterpret_cast<const char *>(flashStr));
  }
}

RFlashStringRef::RFlashStringRef(const RFlashStringRef &stringRef)
  : mStr(stringRef.mStr)
  , mLength(stringRef.mLength)
{
}

RFlashStringRef::~RFlashStringRef()
{
}

unsigned int
RFlashStringRef::length() const
{
  return mLength;
}

char
RFlashStringRef::charAt(unsigned int index) const
{
  if(index >= length())
  {
    return '\0';
  }

  return pgm_read_byte_far(reinterpret_cast<const char *>(mStr) + index);
}
