/**
 * @file RFormatter.h
 *
 * @date 2015-10-25
 * @author Hong-She Liang <starofrainnight@gmail.com>
 */

#ifndef __INCLUDED_DB42F20C7AF911E5AA6EA088B4D1658C
#define __INCLUDED_DB42F20C7AF911E5AA6EA088B4D1658C

#include "RGlobal.h"
#include "RAbstractStringRef.h"
#include "RUniquePointer.h"
#include <Print.h>

/**
 * Provided a printf like method to directly output to Print objects.
 *
 * @code
 * RFormatter(&Serial).parse("There have %*%s people living .").arg(12);
 * @endcode
 *
 * The codes above output :
 *
 * @code
 * There have 12% people living.
 * @endcode
 *
 * The format rule is very simple:
 *
 * "%s" matched each arg()
 * "%%" eascpe the "%" character
 *
 * The last arg() is required to output rest text!
 *
 */
class RFormatter
{
public:
  RFormatter(Stream *stream);

  RFormatter &
  operator ()(const char *format);
  RFormatter &
  operator ()(const rfchar *format);
  RFormatter &
  operator ()(const String *format);

  template <class ... ParamTypes>
  RFormatter &
  arg(ParamTypes ... params)
  {
    if(printBeforeNextMark())
    {
      mStream->print(params ...);
      mFormatIndex += 2;
      printBeforeNextMark();
    }

    return *this;
  }

  bool
  isFinished();
  Stream *
  stream();

private:
  bool
  printBeforeNextMark();

private:
  Stream *mStream;

  RUniquePointer<RAbstractStringRef> mFormat;
  unsigned int mFormatIndex;

private:
  R_DISABLE_COPY(RFormatter)
};

#endif /* __INCLUDED_DB42F20C7AF911E5AA6EA088B4D1658C */
