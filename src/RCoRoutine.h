#ifndef __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
#define __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C

#include "RObject.h"
#include <pt.h>

/**
 * @brief The RCoRoutine class
 *
 * CoRoutine design, not yet implemented.
 */
class RCoRoutine : public RObject
{
public:
  RCoRoutine();
  virtual
  ~RCoRoutine();

  virtual char
  run();

  R_DECLARE_PRIVATE(RCoRoutine);
};

#endif // __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
