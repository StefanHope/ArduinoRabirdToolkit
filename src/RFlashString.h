#ifndef __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
#define __INCLUDED_675A3F04598211E6AA6EA088B4D1658C

#include <WString.h>

class RFlashString
{
private:
  class __FlashStringHelper *mStr;

public:
  RFlashString(class __FlashStringHelper *flashStr);
  ~RFlashString();
};

#endif // __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
