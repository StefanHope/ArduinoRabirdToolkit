# 2 "TestStringRefs.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>
#include <RAbstractStringRef.h>
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

RTEST(TestAbstractStringRef)
{
  const char *normalString0 = "";
  const char *normalString1 = "a";
  const char *normalString2 = "ab";
  const char *normalString3 = "abc";
  const char *normalString4 = "AbC";

  // length
  RASSERT_EQUAL(BasicStringRef(normalString0).length(), strlen(normalString0));
  RASSERT_EQUAL(BasicStringRef(normalString1).length(), strlen(normalString1));
  RASSERT_EQUAL(BasicStringRef(normalString2).length(), strlen(normalString2));
  RASSERT_EQUAL(BasicStringRef(normalString3).length(), strlen(normalString3));

  // compareTo
  RASSERT_EQUAL(BasicStringRef(normalString3).compareTo(BasicStringRef(
                                                          normalString3)), 0);
  RASSERT_MORE(BasicStringRef(normalString3).compareTo(BasicStringRef(
                                                         normalString2)), 0);
  RASSERT_MORE(BasicStringRef(normalString3).compareTo(BasicStringRef(
                                                         normalString1)), 0);
  RASSERT_MORE(BasicStringRef(normalString3).compareTo(BasicStringRef(
                                                         normalString0)), 0);

  RASSERT_LESS(BasicStringRef(normalString0).compareTo(BasicStringRef(
                                                         normalString3)), 0);
  RASSERT_LESS(BasicStringRef(normalString0).compareTo(BasicStringRef(
                                                         normalString2)), 0);
  RASSERT_LESS(BasicStringRef(normalString0).compareTo(BasicStringRef(
                                                         normalString1)), 0);
  RASSERT_LESS(BasicStringRef(normalString0).compareTo(BasicStringRef(
                                                         normalString0)), 0);

  RASSERT_EQUAL(BasicStringRef(normalString3).compareTo((normalString3)), 0);
  RASSERT_MORE(BasicStringRef(normalString3).compareTo((normalString2)), 0);
  RASSERT_MORE(BasicStringRef(normalString3).compareTo((normalString1)), 0);
  RASSERT_MORE(BasicStringRef(normalString3).compareTo((normalString0)), 0);

  RASSERT_LESS(BasicStringRef(normalString0).compareTo((normalString3)), 0);
  RASSERT_LESS(BasicStringRef(normalString0).compareTo((normalString2)), 0);
  RASSERT_LESS(BasicStringRef(normalString0).compareTo((normalString1)), 0);
  RASSERT_LESS(BasicStringRef(normalString0).compareTo((normalString0)), 0);

  // equals
  RASSERT_TRUE(BasicStringRef(normalString3).equals(BasicStringRef(
                                                      normalString3)));
  RASSERT_TRUE(BasicStringRef(normalString3).equals((normalString3)));

  // equalsIgnoreCase
  RASSERT_TRUE(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(
                                                                normalString4)));
  RASSERT_TRUE(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(
                                                                normalString3)));
  RASSERT_FALSE(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(
                                                                 normalString2)));
  RASSERT_FALSE(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(
                                                                 normalString0)));

  // startsWith
  RASSERT_TRUE(BasicStringRef(normalString3).startsWith(BasicStringRef(
                                                          normalString3)));
  RASSERT_TRUE(BasicStringRef(normalString3).startsWith(BasicStringRef(
                                                          normalString2)));
  RASSERT_TRUE(BasicStringRef(normalString3).startsWith(BasicStringRef(
                                                          normalString1)));
  RASSERT_FALSE(BasicStringRef(normalString3).startsWith(BasicStringRef(
                                                           normalString0)));

  // endsWith
  RASSERT_TRUE(BasicStringRef(normalString3).endsWith(BasicStringRef("c")));
  RASSERT_TRUE(BasicStringRef(normalString3).endsWith(BasicStringRef("bc")));
  RASSERT_TRUE(BasicStringRef(normalString3).endsWith(BasicStringRef("abc")));
  RASSERT_FALSE(BasicStringRef(normalString3).endsWith(BasicStringRef("")));

  // charAt
  RASSERT_TRUE(BasicStringRef(normalString3).charAt(0) == 'a');
  RASSERT_TRUE(BasicStringRef(normalString3).charAt(1) == 'b');
  RASSERT_TRUE(BasicStringRef(normalString3).charAt(2) == 'c');
  RASSERT_TRUE(BasicStringRef(normalString3).charAt(3) == '\0');

  // indexOf
  RASSERT_EQUAL(BasicStringRef(normalString3).indexOf('a'), 0);
  RASSERT_EQUAL(BasicStringRef(normalString3).indexOf('b'), 1);
  RASSERT_EQUAL(BasicStringRef(normalString3).indexOf('c'), 2);
  RASSERT_EQUAL(BasicStringRef(normalString3).indexOf('d'), -1);

  // lastIndexOf
  RASSERT_EQUAL(BasicStringRef(normalString3).lastIndexOf('a'), 0);
  RASSERT_EQUAL(BasicStringRef(normalString3).lastIndexOf('b'), 1);
  RASSERT_EQUAL(BasicStringRef(normalString3).lastIndexOf('c'), 2);
  RASSERT_EQUAL(BasicStringRef(normalString3).lastIndexOf('d'), -1);

  // operator ==
  RASSERT_TRUE(BasicStringRef(normalString3) == BasicStringRef(normalString3));
  RASSERT_TRUE(BasicStringRef(normalString3) == normalString3);

  // operator !=
  RASSERT_TRUE(BasicStringRef(normalString3) != BasicStringRef(normalString3));
  RASSERT_TRUE(BasicStringRef(normalString3) != BasicStringRef(normalString0));

  // operator >
  RASSERT_TRUE(BasicStringRef(normalString3) > BasicStringRef(normalString2));
  RASSERT_TRUE(BasicStringRef(normalString3) > BasicStringRef(normalString0));

  // operator <
  RASSERT_TRUE(BasicStringRef(normalString1) < BasicStringRef(normalString3));
  RASSERT_TRUE(BasicStringRef(normalString1) < BasicStringRef(normalString2));

  // operator <=
  RASSERT_TRUE(BasicStringRef(normalString2) <= BasicStringRef(normalString3));
  RASSERT_TRUE(BasicStringRef(normalString2) <= BasicStringRef(normalString2));
  RASSERT_TRUE(BasicStringRef(normalString2) <= BasicStringRef(normalString1));
  RASSERT_FALSE(BasicStringRef(normalString2) <= BasicStringRef(normalString0));

  // operator >=
  RASSERT_FALSE(BasicStringRef(normalString2) >= BasicStringRef(normalString3));
  RASSERT_TRUE(BasicStringRef(normalString2) >= BasicStringRef(normalString2));
  RASSERT_TRUE(BasicStringRef(normalString2) >= BasicStringRef(normalString1));
  RASSERT_TRUE(BasicStringRef(normalString2) >= BasicStringRef(normalString0));
}

void
setup()
{
  Serial.begin(9600);

  while(!Serial)  // for the Arduino Leonardo/Micro only
  {
  }

  RTestApplication testApp;

  testApp.addTest(&RTEST_INSTANCE(TestAbstractStringRef));
  testApp.run();
}

void
loop()
{
}
