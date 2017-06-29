#ifndef __INCLUDED_72B5181CFC9111E6AA6EA088B4D1658C
#define __INCLUDED_72B5181CFC9111E6AA6EA088B4D1658C

#include "RGlobal.h"

class RThread;
class RObject;
class REvent;

R_EXTERN_C int
rMain(int argc, rfchar *argv[]);
R_EXTERN_C RThread *
rGetMainThread();
R_EXTERN_C
void
rPostEvent(RObject *receiver, REvent *event);

#endif // __INCLUDED_72B5181CFC9111E6AA6EA088B4D1658C
