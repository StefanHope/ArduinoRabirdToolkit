#ifndef _INCLUDED_CEFD8F1A5D4C11E68E7800F1F38F93EF
#define _INCLUDED_CEFD8F1A5D4C11E68E7800F1F38F93EF

class RAbstractStringRef
{
public:
  RAbstractStringRef();

//  virtual unsigned int length(void) const = 0;
//  virtual int compareTo(const RAbstractStringRef &s) const = 0;
//  virtual unsigned char equals(const RAbstractStringRef &s) const = 0;
//  virtual unsigned char equals(const char *cstr) const = 0;
//  unsigned char operator == (const RAbstractStringRef &rhs) const {return equals(rhs);} = 0;
//  unsigned char operator == (const char *cstr) const {return equals(cstr);}
//  unsigned char operator != (const RAbstractStringRef &rhs) const {return !equals(rhs);}
//  unsigned char operator != (const char *cstr) const {return !equals(cstr);}
//  virtual unsigned char operator <  (const RAbstractStringRef &rhs) const;
//  virtual unsigned char operator >  (const RAbstractStringRef &rhs) const;
//  virtual unsigned char operator <= (const RAbstractStringRef &rhs) const;
//  virtual unsigned char operator >= (const RAbstractStringRef &rhs) const;
//  virtual unsigned char equalsIgnoreCase(const RAbstractStringRef &s) const;
//  virtual unsigned char startsWith( const RAbstractStringRef &prefix) const;
//  virtual unsigned char startsWith(const RAbstractStringRef &prefix, unsigned int offset) const;
//  virtual unsigned char endsWith(const RAbstractStringRef &suffix) const;

//  // character acccess
//  char charAt(unsigned int index) const;
//  void setCharAt(unsigned int index, char c);
//  char operator [] (unsigned int index) const;
//  char& operator [] (unsigned int index);
//  void getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index=0) const;
//  void toCharArray(char *buf, unsigned int bufsize, unsigned int index=0) const
//    {getBytes((unsigned char *)buf, bufsize, index);}
//  const char * c_str() const { return buffer; }
//  const char* begin() { return c_str(); }
//  const char* end() { return c_str() + length(); }

//  // search
//  int indexOf( char ch ) const;
//  int indexOf( char ch, unsigned int fromIndex ) const;
//  int indexOf( const RAbstractStringRef &str ) const;
//  int indexOf( const RAbstractStringRef &str, unsigned int fromIndex ) const;
//  int lastIndexOf( char ch ) const;
//  int lastIndexOf( char ch, unsigned int fromIndex ) const;
//  int lastIndexOf( const RAbstractStringRef &str ) const;
//  int lastIndexOf( const RAbstractStringRef &str, unsigned int fromIndex ) const;
};

#endif // _INCLUDED_CEFD8F1A5D4C11E68E7800F1F38F93EF
