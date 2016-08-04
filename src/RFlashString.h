#ifndef __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
#define __INCLUDED_675A3F04598211E6AA6EA088B4D1658C

#include "RTypes.h"
#include <WString.h>
#include <Printable.h>

class RFlashString
{
private:
  uintptr_t mStr;

public:
  RFlashString(const class __FlashStringHelper *flashStr);
  ~RFlashString();

  __FlashStringHelper *
  data()
  {
    return rLengthenPtr<__FlashStringHelper *>(mStr);
  }

  operator __FlashStringHelper*()
  {
      return data();
  }

  /// Support if(flashStr) style
  operator bool()
  {
    return mStr != 0;
  }
};

#endif // __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
