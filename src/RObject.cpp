#include "RObject.h"

size_t
RObject::printTo(Print& p) const
{
  size_t size = 0;

  size += p.print(F("RObject(0x"));
  size += p.print(
        static_cast<uintptr_t>(reinterpret_cast<int>(this)), HEX);
  size += p.print(F(")"));

  return size;
}
