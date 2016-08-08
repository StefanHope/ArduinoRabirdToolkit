
#include "RFormatter.h"
#include <Print.h>

RFormatter::RFormatter(Print *print)
  : mPrint(print), mFormat("")
{
}

RFormatter &RFormatter::parse(const char * format)
{
  mFormat = format;
  // If this message does not have any format mark, we just print the
  // whole string.
  printBeforeNextMark();
  return *this;
}

bool RFormatter::printBeforeNextMark()
{
  char c;
  char nextChar;

  while(1) {
    c = *mFormat;
    if ('\0' == c) {
      break;
    }

    if ('%' == c) {
      ++ mFormat;

      nextChar = *mFormat;
      if ('%' == nextChar) {
        // '%%' means one '%'
        mPrint->write(nextChar);
        ++ mFormat;
      } else if ('s' == nextChar) {
        // Found replacement mark : "%s"
        -- mFormat; // Jump to forward "%"
        return true;
      } else if ('\0' == nextChar) {
        mPrint->write(c);
        break;
      } else {
        mPrint->write(c);
        mPrint->write(nextChar);
        ++ mFormat;
      }
    } else {
      mPrint->write(c);
      ++ mFormat;
    }
  }

  return false;
}

