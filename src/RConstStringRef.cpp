#include "RConstStringRef.h"
#include <stdlib.h>
#include <string.h>

RConstStringRef::RConstStringRef(): mStr(NULL), mLength(0)
{
}

RConstStringRef::RConstStringRef(const char *str): mStr(str), mLength(0)
{
  if(NULL != str)
  {
    mLength = strlen(str);
  }
}

unsigned int
RConstStringRef::length() const
{
  return mLength;
}

char
RConstStringRef::charAt(unsigned int index) const
{
  if(index >= mLength)
  {
    return '\0';
  }

  return mStr[index];
}
