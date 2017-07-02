#ifndef __INCLUDED_0AED2A7C5E6011E7AA6EA088B4D1658C
#define __INCLUDED_0AED2A7C5E6011E7AA6EA088B4D1658C

#include <RObject.h>
#include <list>

class RRealtimeTimer;

struct RTimerQueueItem
{
  RRealtimeTimer *timer;
  /**
   * @brief Expiry in ms
   *
   * This value will be calculated when start the timer.
   */
  uint32_t expiry;
};

typedef std::list<RTimerQueueItem> RTimerQueue;

#endif // __INCLUDED_0AED2A7C5E6011E7AA6EA088B4D1658C
