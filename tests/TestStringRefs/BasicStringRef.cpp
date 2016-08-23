#include "BasicStringRef.h"
#include <string.h>

BasicStringRef::BasicStringRef(const char *str) : RAbstractStringRef(),
  mStr(str), mLength(0)
{
  if(NULL != str)
  {
    mLength = rSignedCast(strlen(str));
  }
}

BasicStringRef::~BasicStringRef()
{
}
