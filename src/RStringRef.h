#ifndef __INCLUDED_0D4A5BE6605511E683A100F1F38F93EF
#define __INCLUDED_0D4A5BE6605511E683A100F1F38F93EF

#include "RAbstractStringRef.h"
#include "WString.h"

class RStringRef : public RAbstractStringRef
{
public:
  RStringRef(const String *str);
  RStringRef(const RStringRef &stringRef);

  // RAbstractStringRef interfaces:
  unsigned int
  length() const;

  char
  charAt(unsigned int index) const;

private:
  const String *mStr;
};

#endif // __INCLUDED_0D4A5BE6605511E683A100F1F38F93EF
