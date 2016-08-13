#include "RAbstractStringRef.h"

RAbstractStringRef::RAbstractStringRef()
{
}

RAbstractStringRef::~RAbstractStringRef()
{
}

unsigned char
RAbstractStringRef::equals(const RAbstractStringRef &s) const
{
  return compareTo(s) == 0;
}

unsigned char
RAbstractStringRef::equals(const char *cstr) const
{
  return compareTo(cstr) == 0;
}

unsigned char
RAbstractStringRef::operator ==(const RAbstractStringRef &rhs) const
{
  return equals(rhs);
}

unsigned char
RAbstractStringRef::operator ==(const char *cstr) const
{
  return equals(cstr);
}

unsigned char
RAbstractStringRef::operator !=(const RAbstractStringRef &rhs) const
{
  return !equals(rhs);
}

unsigned char
RAbstractStringRef::operator !=(const char *cstr) const
{
  return !equals(cstr);
}

unsigned char
RAbstractStringRef::operator <(const RAbstractStringRef &rhs) const
{
  return compareTo(rhs) < 0;
}

unsigned char
RAbstractStringRef::operator >(const RAbstractStringRef &rhs) const
{
  return compareTo(rhs) > 0;
}

unsigned char
RAbstractStringRef::operator <=(const RAbstractStringRef &rhs) const
{
  return compareTo(rhs) <= 0;
}

unsigned char
RAbstractStringRef::operator >=(const RAbstractStringRef &rhs) const
{
  return compareTo(rhs) >= 0;
}

unsigned char
RAbstractStringRef::startsWith(const RAbstractStringRef &prefix) const
{
  return startsWith(prefix, 0);
}

unsigned char
RAbstractStringRef::endsWith(const RAbstractStringRef &suffix) const
{
  if((suffix.length() <= 0) || (suffix.length() > length()))
  {
    return false;
  }

  return startsWith(suffix, length() - suffix.length());
}

unsigned char
RAbstractStringRef::startsWith(const RAbstractStringRef &prefix, unsigned int offset) const
{
  if((offset >= length())
     || (prefix.length() <= 0)
     || (prefix.length() > (length() - offset)))
  {
    return false;
  }

  for(unsigned int i = 0; i < prefix.length(); ++ i, ++ offset)
  {
    if(charAt(offset) != prefix.charAt(i))
    {
      return false;
    }
  }

  return true;
}

char
RAbstractStringRef::operator [](unsigned int index) const
{
  return charAt(index);
}

void
RAbstractStringRef::getBytes(unsigned char *buf, unsigned int bufsize,
                             unsigned int index) const
{
  if(!bufsize || !buf)
  {
    return;
  }

  if(index >= length())
  {
    buf[0] = 0;
    return;
  }

  unsigned int copySize = 0;

  copySize = length() - index - 1;
  if(bufsize < copySize)
  {
    copySize = bufsize;
  }

  // Very slow way to copy bytes, you have better override this copy method!
  unsigned char *bufEnd = buf + copySize;

  for(; buf < bufEnd; ++buf, ++index)
  {
    *buf = static_cast<unsigned char>(charAt(index));
  }
  *buf = 0;
}

void
RAbstractStringRef::toCharArray(char *buf, unsigned int bufsize,
                                unsigned int index) const
{
  getBytes(reinterpret_cast<unsigned char *>(buf), bufsize, index);
}

int RAbstractStringRef::indexOf(char ch) const
{
  return indexOf(ch, 0);
}

int RAbstractStringRef::indexOf(char ch, unsigned int fromIndex) const
{
  if(fromIndex >= length())
  {
    return -1;
  }

  for(unsigned int i = 0; i < length(); ++i)
  {
    if(charAt(i) == ch)
    {
      return static_cast<int>(i);
    }
  }

  return -1;
}

int RAbstractStringRef::indexOf(const RAbstractStringRef &str) const
{
  return indexOf(str, 0);
}

int RAbstractStringRef::indexOf(const RAbstractStringRef &str, unsigned int fromIndex) const
{
  if((fromIndex >= length())
     || (str.length() <= 0)
     || (str.length() > (length() - fromIndex)))
  {
    return -1;
  }

  for(; fromIndex < length(); ++fromIndex)
  {
    unsigned int i = fromIndex;
    unsigned int j = 0;
    bool isSuccessed = true;

    for(; j < str.length(); ++j, ++i)
    {
      if(charAt(i) != str.charAt(j))
      {
        isSuccessed = false;
        break;
      }
    }

    if(isSuccessed)
    {
      return static_cast<int>(fromIndex);
    }
  }

  return -1;
}

int RAbstractStringRef::lastIndexOf(char ch) const
{
  if(length() == 0)
  {
    return -1;
  }

  return lastIndexOf(ch, length() - 1);
}

int RAbstractStringRef::lastIndexOf(char ch, unsigned int fromIndex) const
{
  if(fromIndex >= length())
  {
    return -1;
  }

  // Very slow way, you have better override this method!
  for(++fromIndex; fromIndex > 0;)
  {
    -- fromIndex;

    if(charAt(fromIndex) == ch)
    {
      return static_cast<int>(fromIndex);
    }
  }

  return -1;
}

int RAbstractStringRef::lastIndexOf(const RAbstractStringRef &str) const
{
  return lastIndexOf(str, 0);
}

int RAbstractStringRef::lastIndexOf(const RAbstractStringRef &str, unsigned int fromIndex) const
{
  if((fromIndex >= length())
     || (str.length() <= 0)
     || (str.length() > (fromIndex + 1)))
  {
    return -1;
  }

  // Very slow way, you have better override this method!
  for(++ fromIndex; fromIndex > str.length(); )
  {
    -- fromIndex;

    unsigned int i = fromIndex - (str.length() - 1);
    unsigned int j = 0;
    bool isSuccessed = true;

    for(; j < str.length(); ++j, ++i)
    {
      if(charAt(i) != str.charAt(j))
      {
        isSuccessed = false;
        break;
      }
    }

    if(isSuccessed)
    {
      return static_cast<int>(fromIndex);
    }
  }

  return -1;
}
