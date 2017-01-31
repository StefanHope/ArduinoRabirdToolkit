#include "RStringRef.h"

RStringRef::RStringRef(const String *str)
  : mStr(str)
{
}

RStringRef::RStringRef(const RStringRef &stringRef)
  : mStr(stringRef.mStr)
{
}

unsigned int
RStringRef::length() const
{
  if(mStr)
  {
    return mStr->length();
  }
  else
  {
    return 0;
  }
}

char
RStringRef::charAt(unsigned int index) const
{
  if((NULL == mStr) || (index >= length()))
  {
    return '\0';
  }

  return mStr->charAt(index);
}
