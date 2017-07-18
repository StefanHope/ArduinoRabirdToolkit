#include "RByteOrder.h"

static volatile int8_t sByteOrder = -1;

uint8_t
rDetectByteOrder()
{
  const uint16_t value = 0x1234;

  return ((*(uint8_t *)&value) == 0x12) ? R_BIG_ENDIAN : R_LITTLE_ENDIAN;
}

uint16_t
rHtons(uint16_t value)
{
  if(sByteOrder < 0)
  {
    sByteOrder = static_cast<int8_t>(rDetectByteOrder());
  }

  if(R_BIG_ENDIAN == sByteOrder)
  {
    return value;
  }
  else
  {
    return rReverseByteOrderS(value);
  }
}

uint32_t
rHtonl(uint32_t value)
{
  if(sByteOrder < 0)
  {
    sByteOrder = static_cast<int8_t>(rDetectByteOrder());
  }

  if(R_BIG_ENDIAN == sByteOrder)
  {
    return value;
  }
  else
  {
    return rReverseByteOrderL(value);
  }
}

uint64_t
rHtonll(uint64_t value)
{
  if(sByteOrder < 0)
  {
    sByteOrder = static_cast<int8_t>(rDetectByteOrder());
  }

  if(R_BIG_ENDIAN == sByteOrder)
  {
    return value;
  }
  else
  {
    return rReverseByteOrderLL(value);
  }
}
