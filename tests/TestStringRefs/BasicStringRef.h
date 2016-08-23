#ifndef __INCLUDED_03496C6668CC11E6AA6E0021CC66E280
#define __INCLUDED_03496C6668CC11E6AA6E0021CC66E280

#include <RAbstractStringRef.h>

class BasicStringRef :
  public RAbstractStringRef
{
public:
  BasicStringRef(const char *str);
  ~BasicStringRef();

  unsigned int
  length(void) const
  {
    return static_cast<unsigned int>(mLength);
  }

  char
  charAt(unsigned int index) const
  {
    if((NULL == mStr) || (index >= length()))
    {
      return '\0';
    }

    return mStr[index];
  }

private:
  const char *mStr;
  rnumber_t   mLength;
};

#endif // __INCLUDED_03496C6668CC11E6AA6E0021CC66E280
