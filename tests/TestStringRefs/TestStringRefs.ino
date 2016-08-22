# 2 "TestStringRefs.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>
#include <RAbstractStringRef.h>
#include <RConstStringRef.h>
#include <RStringRef.h>
#include <RFlashStringRef.h>
#include <RTest.h>
#include <string.h>

class BasicStringRef:
public RAbstractStringRef
{
public:
  BasicStringRef(const char *str);
  ~BasicStringRef();

  unsigned int
  length(void) const
  {
    return static_cast < unsigned int > (mLength);
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

BasicStringRef::BasicStringRef(const char *str) : RAbstractStringRef(),
  mStr(str), mLength(0)
{
  if(NULL != str)
  {
    mLength = rSignedCast(strlen(str));
  }
}

BasicStringRef::~BasicStringRef()
{
}

template < class DerivedType, class StringRefType >
class BasicTestStringRef:
public RTest
{
public:
  typedef BasicTestStringRef < DerivedType, StringRefType > ThisType;

  BasicTestStringRef(const __FlashStringHelper * str)
    : RTest(str)
    , mNormalString0("")
    , mNormalString1("a")
    , mNormalString2("ab")
    , mNormalString3("abc")
    , mNormalString4("AbC")
    , mFlashString0(F(""))
    , mFlashString1(F("a"))
    , mFlashString2(F("ab"))
    , mFlashString3(F("abc"))
    , mFlashString4(F("AbC"))
    , mString0("")
    , mString1("a")
    , mString2("ab")
    , mString3("abc")
    , mString4("Abc")
  {
  }

  void
  run()
  {
    const StringRefType &
    stringRef0(getDerived()->mStringRef0);
    const StringRefType &
    stringRef1(getDerived()->mStringRef1);
    const StringRefType &
    stringRef2(getDerived()->mStringRef2);
    const StringRefType &
    stringRef3(getDerived()->mStringRef3);
    const StringRefType &
    stringRef4(getDerived()->mStringRef4);

    // length
    RASSERT_EQUAL(stringRef0.length(), strlen(mNormalString0));
    RASSERT_EQUAL(stringRef1.length(), strlen(mNormalString1));
    RASSERT_EQUAL(stringRef2.length(), strlen(mNormalString2));
    RASSERT_EQUAL(stringRef3.length(), strlen(mNormalString3));

    // compareTo
    RASSERT_EQUAL(stringRef3.compareTo(stringRef3), 0);
    RASSERT_MORE(stringRef3.compareTo(stringRef2), 0);
    RASSERT_MORE(stringRef3.compareTo(stringRef1), 0);
    RASSERT_MORE(stringRef3.compareTo(stringRef0), 0);

    RASSERT_LESS(stringRef0.compareTo(stringRef3), 0);
    RASSERT_LESS(stringRef0.compareTo(stringRef2), 0);
    RASSERT_LESS(stringRef0.compareTo(stringRef1), 0);
    RASSERT_LESS(stringRef0.compareTo(stringRef0), 0);

    RASSERT_EQUAL(stringRef3.compareTo((mNormalString3)), 0);
    RASSERT_MORE(stringRef3.compareTo((mNormalString2)), 0);
    RASSERT_MORE(stringRef3.compareTo((mNormalString1)), 0);
    RASSERT_MORE(stringRef3.compareTo((mNormalString0)), 0);

    RASSERT_LESS(stringRef0.compareTo((mNormalString3)), 0);
    RASSERT_LESS(stringRef0.compareTo((mNormalString2)), 0);
    RASSERT_LESS(stringRef0.compareTo((mNormalString1)), 0);
    RASSERT_LESS(stringRef0.compareTo((mNormalString0)), 0);

    // equals
    RASSERT_TRUE(stringRef3.equals(stringRef3));
    RASSERT_TRUE(stringRef3.equals((mNormalString3)));

    // equalsIgnoreCase
    RASSERT_TRUE(stringRef3.equalsIgnoreCase(stringRef4));
    RASSERT_TRUE(stringRef3.equalsIgnoreCase(stringRef3));
    RASSERT_FALSE(stringRef3.equalsIgnoreCase(stringRef2));
    RASSERT_FALSE(stringRef3.equalsIgnoreCase(stringRef0));

    // startsWith
    RASSERT_TRUE(stringRef3.startsWith(stringRef3));
    RASSERT_TRUE(stringRef3.startsWith(stringRef2));
    RASSERT_TRUE(stringRef3.startsWith(stringRef1));
    RASSERT_FALSE(stringRef3.startsWith(stringRef0));

    // endsWith
    RASSERT_TRUE(stringRef3.endsWith(BasicStringRef("c")));
    RASSERT_TRUE(stringRef3.endsWith(BasicStringRef("bc")));
    RASSERT_TRUE(stringRef3.endsWith(BasicStringRef("abc")));
    RASSERT_FALSE(stringRef3.endsWith(BasicStringRef("")));

    // charAt
    RASSERT_TRUE(stringRef3.charAt(0) == 'a');
    RASSERT_TRUE(stringRef3.charAt(1) == 'b');
    RASSERT_TRUE(stringRef3.charAt(2) == 'c');
    RASSERT_TRUE(stringRef3.charAt(3) == '\0');

    // indexOf
    RASSERT_EQUAL(stringRef3.indexOf('a'), 0);
    RASSERT_EQUAL(stringRef3.indexOf('b'), 1);
    RASSERT_EQUAL(stringRef3.indexOf('c'), 2);
    RASSERT_EQUAL(stringRef3.indexOf('d'), -1);

    // lastIndexOf
    RASSERT_EQUAL(stringRef3.lastIndexOf('a'), 0);
    RASSERT_EQUAL(stringRef3.lastIndexOf('b'), 1);
    RASSERT_EQUAL(stringRef3.lastIndexOf('c'), 2);
    RASSERT_EQUAL(stringRef3.lastIndexOf('d'), -1);

    // operator ==
    RASSERT_TRUE(stringRef3 == stringRef3);
    RASSERT_TRUE(stringRef3 == mNormalString3);

    // operator !=
    RASSERT_TRUE(stringRef3 != stringRef3);
    RASSERT_TRUE(stringRef3 != stringRef0);

    // operator >
    RASSERT_TRUE(stringRef3 > stringRef2);
    RASSERT_TRUE(stringRef3 > stringRef0);

    // operator <
    RASSERT_TRUE(stringRef1 < stringRef3);
    RASSERT_TRUE(stringRef1 < stringRef2);

    // operator <=
    RASSERT_TRUE(stringRef2 <= stringRef3);
    RASSERT_TRUE(stringRef2 <= stringRef2);
    RASSERT_TRUE(stringRef2 <= stringRef1);
    RASSERT_FALSE(stringRef2 <= stringRef0);

    // operator >=
    RASSERT_FALSE(stringRef2 >= stringRef3);
    RASSERT_TRUE(stringRef2 >= stringRef2);
    RASSERT_TRUE(stringRef2 >= stringRef1);
    RASSERT_TRUE(stringRef2 >= stringRef0);
  }

protected:
  inline
  DerivedType *
  getDerived()
  {
    return static_cast < DerivedType * > (const_cast < ThisType * > (this));
  }

  inline
  const DerivedType *
  getDerived() const
  {
    return static_cast < DerivedType * > (const_cast < ThisType * > (this));
  }

public:
  const char *mNormalString0;
  const char *mNormalString1;
  const char *mNormalString2;
  const char *mNormalString3;
  const char *mNormalString4;

  const __FlashStringHelper *mFlashString0;
  const __FlashStringHelper *mFlashString1;
  const __FlashStringHelper *mFlashString2;
  const __FlashStringHelper *mFlashString3;
  const __FlashStringHelper *mFlashString4;

  String mString0;
  String mString1;
  String mString2;
  String mString3;
  String mString4;
};
class TestBasicStringRef
: public BasicTestStringRef < TestBasicStringRef, BasicStringRef >
{
public:
  typedef BasicStringRef                                           StringRefType;
  typedef BasicTestStringRef < TestBasicStringRef, StringRefType > BaseType;

  TestBasicStringRef()
    : BaseType(F("TestBasicStringRef"))
    , mStringRef0(mNormalString0)
    , mStringRef1(mNormalString1)
    , mStringRef2(mNormalString2)
    , mStringRef3(mNormalString3)
    , mStringRef4(mNormalString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
}

class TestConstStringRef
: public BasicTestStringRef < TestConstStringRef, RConstStringRef >
{
public:
  typedef RConstStringRef
    StringRefType;
  typedef BasicTestStringRef < TestConstStringRef, RConstStringRef > BaseType;

  TestConstStringRef()
    : BaseType(F("TestConstStringRef"))
    , mStringRef0(mNormalString0)
    , mStringRef1(mNormalString1)
    , mStringRef2(mNormalString2)
    , mStringRef3(mNormalString3)
    , mStringRef4(mNormalString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
}

class TestFlashStringRef
: public BasicTestStringRef < TestFlashStringRef, RFlashStringRef >
{
public:
  typedef RFlashStringRef                                          StringRefType;
  typedef BasicTestStringRef < TestFlashStringRef, StringRefType > BaseType;

  TestFlashStringRef()
    : BaseType(F("TestFlashStringRef"))
    , mStringRef0(mFlashString0)
    , mStringRef1(mFlashString1)
    , mStringRef2(mFlashString2)
    , mStringRef3(mFlashString3)
    , mStringRef4(mFlashString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
}

class TestStringRef
: public BasicTestStringRef < TestStringRef, RStringRef >
{
public:
  typedef RStringRef                                          StringRefType;
  typedef BasicTestStringRef < TestStringRef, StringRefType > BaseType;

  TestStringRef()
    : BaseType(F("TestStringRef"))
    , mStringRef0(&mString0)
    , mStringRef1(&mString1)
    , mStringRef2(&mString2)
    , mStringRef3(&mString3)
    , mStringRef4(&mString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
}

void
setup()
{
  Serial.begin(9600);

  while(!Serial)  // for the Arduino Leonardo/Micro only
  {
  }

  RTestApplication   testApp;
  TestBasicStringRef testBasicStringRef;
  TestConstStringRef testConstStringRef;
  TestFlashStringRef testFlashStringRef;
  TestStringRef      testStringRef;

  testApp.addTest(&testBasicStringRef);
  testApp.addTest(&testConstStringRef);
  testApp.addTest(&testFlashStringRef);
  testApp.addTest(&testStringRef);
  testApp.run();
}

void
loop()
{
}
