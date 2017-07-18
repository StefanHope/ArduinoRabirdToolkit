#ifndef __INCLUDED_58BCE3726B8B11E7AA6EA088B4D1658C
#define __INCLUDED_58BCE3726B8B11E7AA6EA088B4D1658C

#include <RTypes.h>

#ifndef R_BIG_ENDIAN
#define R_BIG_ENDIAN 34
#endif

#ifndef R_LITTLE_ENDIAN
#define R_LITTLE_ENDIAN 12
#endif

R_EXTERN_C_BLOCK_BEGIN

#define rReverseByteOrderS(value) \
  ((uint16_t)((((value) & 0xff) << 8) \
              | (((value) & 0xff00) >> 8)))

#define rReverseByteOrderL(value) \
  ((uint32_t)((((value) & 0xffl) << 24) \
              | (((value) & 0xff00l) << 8) \
              | (((value) & 0xff0000l) >> 8) \
              | (((value) & 0xff000000l) >> 24)))

#define rReverseByteOrderLL(value) \
  ((uint64_t)((((value) & 0xffll) << 56) \
              | (((value) & 0xff00ll) << 40) \
              | (((value) & 0xff0000ll) << 24) \
              | (((value) & 0xff000000ll) << 8) \
              | (((value) & 0xff00000000ll) >> 8) \
              | (((value) & 0xff0000000000ll) >> 24) \
              | (((value) & 0xff000000000000ll) >> 40) \
              | (((value) & 0xff00000000000000ll) >> 56) \
              ))

uint8_t
rDetectByteOrder();

uint16_t
rHtons(uint16_t value);

uint32_t
rHtonl(uint32_t value);

uint64_t
rHtonll(uint64_t value);

#define rNtohs(value)  rHtons((value))
#define rNtohl(value)  rHtonl((value))
#define rNtohll(value) rHtonll((value))

R_EXTERN_C_BLOCK_END

#endif // __INCLUDED_58BCE3726B8B11E7AA6EA088B4D1658C
