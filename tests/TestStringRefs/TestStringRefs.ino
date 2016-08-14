#include <Arduino.h>
#include <ArduinoUnit.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>
#include <RAbstractStringRef.h>
#include <string.h>

class BasicStringRef: public RAbstractStringRef
{
public:
  BasicStringRef(const char * str);
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
  const char * mStr;
  rnumber_t    mLength;
};

BasicStringRef::BasicStringRef(const char * str): RAbstractStringRef(), mStr(str), mLength(0)
{
  if(NULL != str)
  {
    mLength = rSignedCast(strlen(str));
  }
}

BasicStringRef::~BasicStringRef()
{
}

test(TestAbstractStringRef)
{
  const char * normalString0 = "";
  const char * normalString1 = "a";
  const char * normalString2 = "ab";
  const char * normalString3 = "abc";
  const char * normalString4 = "AbC";

  // length
  assertEqual(BasicStringRef(normalString0).length(), strlen(normalString0));
  assertEqual(BasicStringRef(normalString1).length(), strlen(normalString1));
  assertEqual(BasicStringRef(normalString2).length(), strlen(normalString2));
  assertEqual(BasicStringRef(normalString3).length(), strlen(normalString3));

  // compareTo
  assertEqual(BasicStringRef(normalString3).compareTo(BasicStringRef(normalString3)), 0);
  assertMore(BasicStringRef(normalString3).compareTo(BasicStringRef(normalString2)), 0);
  assertMore(BasicStringRef(normalString3).compareTo(BasicStringRef(normalString1)), 0);
  assertMore(BasicStringRef(normalString3).compareTo(BasicStringRef(normalString0)), 0);

  assertLess(BasicStringRef(normalString0).compareTo(BasicStringRef(normalString3)), 0);
  assertLess(BasicStringRef(normalString0).compareTo(BasicStringRef(normalString2)), 0);
  assertLess(BasicStringRef(normalString0).compareTo(BasicStringRef(normalString1)), 0);
  assertLess(BasicStringRef(normalString0).compareTo(BasicStringRef(normalString0)), 0);

  assertEqual(BasicStringRef(normalString3).compareTo((normalString3)), 0);
  assertMore(BasicStringRef(normalString3).compareTo((normalString2)), 0);
  assertMore(BasicStringRef(normalString3).compareTo((normalString1)), 0);
  assertMore(BasicStringRef(normalString3).compareTo((normalString0)), 0);

  assertLess(BasicStringRef(normalString0).compareTo((normalString3)), 0);
  assertLess(BasicStringRef(normalString0).compareTo((normalString2)), 0);
  assertLess(BasicStringRef(normalString0).compareTo((normalString1)), 0);
  assertLess(BasicStringRef(normalString0).compareTo((normalString0)), 0);

  // equals
  assertTrue(BasicStringRef(normalString3).equals(BasicStringRef(normalString3)));
  assertTrue(BasicStringRef(normalString3).equals((normalString3)));

  // equalsIgnoreCase
  assertTrue(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(normalString4)));
  assertTrue(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(normalString3)));
  assertFalse(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(normalString2)));
  assertFalse(BasicStringRef(normalString3).equalsIgnoreCase(BasicStringRef(normalString0)));

  // startsWith
  assertTrue(BasicStringRef(normalString3).startsWith(BasicStringRef(normalString3)));
  assertTrue(BasicStringRef(normalString3).startsWith(BasicStringRef(normalString2)));
  assertTrue(BasicStringRef(normalString3).startsWith(BasicStringRef(normalString1)));
  assertFalse(BasicStringRef(normalString3).startsWith(BasicStringRef(normalString0)));

  // endsWith
  assertTrue(BasicStringRef(normalString3).endsWith(BasicStringRef("c")));
  assertTrue(BasicStringRef(normalString3).endsWith(BasicStringRef("bc")));
  assertTrue(BasicStringRef(normalString3).endsWith(BasicStringRef("abc")));
  assertFalse(BasicStringRef(normalString3).endsWith(BasicStringRef("")));

  // charAt
  assertTrue(BasicStringRef(normalString3).charAt(0) == 'a');
  assertTrue(BasicStringRef(normalString3).charAt(1) == 'b');
  assertTrue(BasicStringRef(normalString3).charAt(2) == 'c');
  assertTrue(BasicStringRef(normalString3).charAt(3) == '\0');

  // indexOf
  assertEqual(BasicStringRef(normalString3).indexOf('a'), 0);
  assertEqual(BasicStringRef(normalString3).indexOf('b'), 1);
  assertEqual(BasicStringRef(normalString3).indexOf('c'), 2);
  assertEqual(BasicStringRef(normalString3).indexOf('d'), -1);

  // lastIndexOf
  assertEqual(BasicStringRef(normalString3).lastIndexOf('a'), 0);
  assertEqual(BasicStringRef(normalString3).lastIndexOf('b'), 1);
  assertEqual(BasicStringRef(normalString3).lastIndexOf('c'), 2);
  assertEqual(BasicStringRef(normalString3).lastIndexOf('d'), -1);

  // operator ==
  assertTrue(BasicStringRef(normalString3) == BasicStringRef(normalString3));
  assertTrue(BasicStringRef(normalString3) == normalString3);

  // operator !=
  assertTrue(BasicStringRef(normalString3) != BasicStringRef(normalString3));
  assertTrue(BasicStringRef(normalString3) != BasicStringRef(normalString0));

  // operator >
  assertTrue(BasicStringRef(normalString3) > BasicStringRef(normalString2));
  assertTrue(BasicStringRef(normalString3) > BasicStringRef(normalString0));

  // operator <
  assertTrue(BasicStringRef(normalString1) < BasicStringRef(normalString3));
  assertTrue(BasicStringRef(normalString1) < BasicStringRef(normalString2));

  // operator <=
  assertTrue(BasicStringRef(normalString2) <= BasicStringRef(normalString3));
  assertTrue(BasicStringRef(normalString2) <= BasicStringRef(normalString2));
  assertTrue(BasicStringRef(normalString2) <= BasicStringRef(normalString1));
  assertFalse(BasicStringRef(normalString2) <= BasicStringRef(normalString0));

  // operator >=
  assertFalse(BasicStringRef(normalString2) >= BasicStringRef(normalString3));
  assertTrue(BasicStringRef(normalString2) >= BasicStringRef(normalString2));
  assertTrue(BasicStringRef(normalString2) >= BasicStringRef(normalString1));
  assertTrue(BasicStringRef(normalString2) >= BasicStringRef(normalString0));
}

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only
}

void loop()
{
  Test::run();
}

