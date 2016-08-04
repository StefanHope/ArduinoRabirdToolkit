#ifndef __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
#define __INCLUDED_675A3F04598211E6AA6EA088B4D1658C

#include "RRawPointer.h"
#include <WString.h>
#include <Printable.h>

class RFlashString
{
private:
  typedef class __FlashStringHelper ValueType;
  RRawPointer<ValueType> mStr;

public:
  RFlashString(const ValueType *flashStr);
  ~RFlashString();

  ValueType *
  data()
  {
    return mStr.data();
  }

  operator ValueType*()
  {
      return data();
  }

  /// Support if(flashStr) style
  operator bool()
  {
    return mStr;
  }
};

#endif // __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
