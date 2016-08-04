#ifndef __INCLUDED_CB5671DA425011E6932B00F1F38F93EF
#define __INCLUDED_CB5671DA425011E6932B00F1F38F93EF

#include "RTypes.h"
#include <Print.h>
#include <Printable.h>

class RObject : protected Printable
{
public:
  RObject(): Printable()
  {
  }

  virtual ~RObject()
  {
  }

  size_t
  printTo(Print& p) const;
};

#endif // __INCLUDED_CB5671DA425011E6932B00F1F38F93EF
