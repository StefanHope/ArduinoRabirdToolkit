#ifndef __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
#define __INCLUDED_675A3F04598211E6AA6EA088B4D1658C

#include "RRawPointer.h"
#include "RAbstractStringRef.h"
#include <Printable.h>

class RFlashStringRef : public RAbstractStringRef
{
public:
  RFlashStringRef(const rfchar *flashStr);
  RFlashStringRef(const RFlashStringRef &stringRef);
  ~RFlashStringRef();

  // RAbstractStringRef interfaces:
  unsigned int
  length() const;

  char
  charAt(unsigned int index) const;

  const rfchar *
  data()
  {
    return mStr;
  }

  bool
  isNull()
  {
    return NULL == mStr;
  }

  operator const rfchar *()
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
   * rfchar is a special type with pointer value may large than
   * normal pointer, so we must not use uintptr_t to express it.
   */
  const rfchar *mStr;
  size_t        mLength;
};

#endif // __INCLUDED_675A3F04598211E6AA6EA088B4D1658C
