#include "RFormatter.h"
#include "RFlashStringRef.h"
#include "RStringRef.h"
#include "RConstStringRef.h"
#include <Print.h>

RFormatter::RFormatter(Print *print)
  : mPrint(print), mFormat(NULL), mFormatIndex(0)
{
}

RFormatter &
RFormatter::operator ()(const char *format)
{
  mFormat.reset(new RConstStringRef(format));
  // If this message does not have any format mark, we just print the
  // whole string.
  printBeforeNextMark();
  return *this;
}

RFormatter &
RFormatter::operator ()(const rfchar *format)
{
  mFormat.reset(new RFlashStringRef(format));
  // If this message does not have any format mark, we just print the
  // whole string.
  printBeforeNextMark();
  return *this;
}

RFormatter &
RFormatter::operator ()(const String *format)
{
  mFormat.reset(new RStringRef(format));
  // If this message does not have any format mark, we just print the
  // whole string.
  printBeforeNextMark();
  return *this;
}

bool
RFormatter::printBeforeNextMark()
{
  if(!mFormat)
  {
    // Do nothing if don't have a format string
    return false;
  }

  char c;
  char nextChar;

  while(1)
  {
    c = mFormat->charAt(mFormatIndex);

    if('\0' == c)
    {
      break;
    }

    if('%' == c)
    {
      ++mFormatIndex;

      nextChar = mFormat->charAt(mFormatIndex);

      if('%' == nextChar)
      {
        // '%%' means one '%'
        mPrint->write(nextChar);
        ++mFormatIndex;
      }
      else if('s' == nextChar)
      {
        // Found replacement mark : "%s"
        --mFormatIndex;  // Jump to forward "%"
        return true;
      }
      else if('\0' == nextChar)
      {
        mPrint->write(c);
        break;
      }
      else
      {
        mPrint->write(c);
        mPrint->write(nextChar);
        ++mFormatIndex;
      }
    }
    else
    {
      mPrint->write(c);
      ++mFormatIndex;
    }
  }

  // The format finished.
  // Free the string reference object as soon as possible, because we are
  // running on resource limitted system.
  mFormat.clear();
  mFormatIndex = 0;

  return false;
}
