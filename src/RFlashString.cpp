#include "RFlashString.h"

RFlashString::RFlashString(const class __FlashStringHelper *flashStr)
  : mStr(rShortenPtr(flashStr))
{
}
