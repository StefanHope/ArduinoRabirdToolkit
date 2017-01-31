#ifndef __INCLUDED_32495286DDE511E6AA6EA088B4D1658C
#define __INCLUDED_32495286DDE511E6AA6EA088B4D1658C

#include "RCoreApplication.h"

class RApplication : public RCoreApplication
{
public:
  RApplication();
};

#define rApp (RApplication::instance())

#endif // __INCLUDED_32495286DDE511E6AA6EA088B4D1658C
