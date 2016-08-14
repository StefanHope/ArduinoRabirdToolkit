#ifndef __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
#define __INCLUDED_675A3F04598211E6AA6EA088B4D1658C

#include "RRawPointer.h"
#include <WString.h>
#include <Printable.h>

class RFlashString
{
private:
  typedef class __FlashStringHelper ValueType;

public:
  RFlashString();
  RFlashString(const ValueType *flashStr);
  ~RFlashString();

  const ValueType *
  data()
  {
    return mStr;
  }

  bool
  isNull()
  {
    return NULL == mStr;
  }

  operator ValueType*()
  {
      return mStr;
  }

  /// Support if(flashStr) style
  operator bool()
  {
    return mStr;
  }

private:
  /**
   * __FlashStringHelper is a special type with pointer value may large than
   * normal pointer, so we must not use uintptr_t to express it.
   */
  const ValueType *mStr;
};

#endif // __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
