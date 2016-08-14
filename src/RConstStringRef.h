#ifndef __INCLUDED_223FADE0620711E6AA6EA088B4D1658C
#define __INCLUDED_223FADE0620711E6AA6EA088B4D1658C

#include "RAbstractStringRef.h"

class RConstStringRef : public RAbstractStringRef
{
public:
  RConstStringRef();
  RConstStringRef(const char *str);

  // RAbstractStringRef interfaces:
  unsigned int
  length() const;

  char
  charAt(unsigned int index) const;

private:
  const char * mStr;
  size_t mLength;
};

#endif // __INCLUDED_223FADE0620711E6AA6EA088B4D1658C
