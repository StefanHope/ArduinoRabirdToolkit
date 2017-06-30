#ifndef __INCLUDED_C478463A5D4711E7AA6EA088B4D1658C
#define __INCLUDED_C478463A5D4711E7AA6EA088B4D1658C

#if defined(R_OS_FREERTOS)
#include "portable/freertos/RRealtimeTimer.h"
#else
#include "portable/nonos/RRealtimeTimer.h"
#endif

#endif // __INCLUDED_C478463A5D4711E7AA6EA088B4D1658C
