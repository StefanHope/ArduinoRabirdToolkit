#ifndef __INCLUDED_FBA4579423DF11E7AA6EA088B4D1658C
#define __INCLUDED_FBA4579423DF11E7AA6EA088B4D1658C

#include "RGlobal.h"

enum RConnectionType
{
  /// If the signal is emitted from a different thread than the receiving
  /// object the signal is blocked, behaving as BlockedConnection. Otherwise,
  /// the slot is invoked directly, behaving as DirectConnection. The type of
  /// connection is determined when the signal is connected.
  AutoConnection,
  DirectConnection,
  ObjectConnection,
  BlockedConnection,
};

template <class T>
class RConnection
{
public:
  typedef T SlotType;

  RConnection(const SlotType &slot, uint8_t aType=AutoConnection)

    : mSlot(slot), mType(aType)
  {
  }

  RConnection(const RConnection &other)
    : mSlot(other.mSlot), mType(other.mType)
  {
  }

  SlotType mSlot;
  uint8_t  mType;
};

#endif // __INCLUDED_FBA4579423DF11E7AA6EA088B4D1658C
