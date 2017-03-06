#include "RTypes.h"
#include "RObject.h"
#include "RThread.h"

bool
rIsObjectInSameThread(const RObject *left, const RObject *right)
{
  if((NULL == left) || (NULL == right))
  {
    return false;
  }

  return (left->thread()->id() == right->thread()->id());
}
