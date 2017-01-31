#ifndef __INCLUDED_BB33D42E68CC11E6AA6E0021CC66E280
#define __INCLUDED_BB33D42E68CC11E6AA6E0021CC66E280

#include "BasicStringRef.h"
#include <RTest.h>

template <class DerivedType, class StringRefType>
class BasicTestStringRef :
  public RTest
{
public:
  typedef BasicTestStringRef<DerivedType, StringRefType> ThisType;

  BasicTestStringRef(const rfchar *str)

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
    RASSERT_EQUAL(stringRef0.compareTo(stringRef0), 0);

    RASSERT_EQUAL(stringRef3.compareTo((mNormalString3)), 0);
    RASSERT_MORE(stringRef3.compareTo((mNormalString2)), 0);
    RASSERT_MORE(stringRef3.compareTo((mNormalString1)), 0);
    RASSERT_MORE(stringRef3.compareTo((mNormalString0)), 0);

    RASSERT_LESS(stringRef0.compareTo((mNormalString3)), 0);
    RASSERT_LESS(stringRef0.compareTo((mNormalString2)), 0);
    RASSERT_LESS(stringRef0.compareTo((mNormalString1)), 0);
    RASSERT_EQUAL(stringRef0.compareTo((mNormalString0)), 0);

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
    RASSERT_EQUAL(stringRef3.charAt(0), 'a');
    RASSERT_EQUAL(stringRef3.charAt(1), 'b');
    RASSERT_EQUAL(stringRef3.charAt(2), 'c');
    RASSERT_EQUAL(stringRef3.charAt(3), '\0');

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
    RASSERT_EQUAL(stringRef3, stringRef3);
    RASSERT_EQUAL(stringRef3, mNormalString3);

    // operator !=
    RASSERT_NOT_EQUAL(stringRef3, stringRef0);
    RASSERT_NOT_EQUAL(stringRef3, stringRef1);
    RASSERT_NOT_EQUAL(stringRef3, stringRef2);
    RASSERT_NOT_EQUAL(stringRef3, stringRef4);
    RASSERT_NOT_EQUAL(stringRef3, mNormalString0);
    RASSERT_NOT_EQUAL(stringRef3, mNormalString1);
    RASSERT_NOT_EQUAL(stringRef3, mNormalString2);
    RASSERT_NOT_EQUAL(stringRef3, mNormalString4);

    // operator >
    RASSERT_MORE(stringRef3, stringRef2);
    RASSERT_MORE(stringRef3, stringRef0);

    // operator <
    RASSERT_LESS(stringRef1, stringRef3);
    RASSERT_LESS(stringRef1, stringRef2);

    // operator <=
    RASSERT_LESS_OR_EQUAL(stringRef2, stringRef3);
    RASSERT_LESS_OR_EQUAL(stringRef2, stringRef2);

    // operator >=
    RASSERT_MORE_OR_EQUAL(stringRef2, stringRef2);
    RASSERT_MORE_OR_EQUAL(stringRef2, stringRef1);
    RASSERT_MORE_OR_EQUAL(stringRef2, stringRef0);
  }

protected:
  inline
  DerivedType *
  getDerived()
  {
    return static_cast<DerivedType *>(const_cast<ThisType *>(this));
  }

  inline
  const DerivedType *
  getDerived() const
  {
    return static_cast<DerivedType *>(const_cast<ThisType *>(this));
  }

public:
  const char *  mNormalString0;
  const char *  mNormalString1;
  const char *  mNormalString2;
  const char *  mNormalString3;
  const char *  mNormalString4;
  const rfchar *mFlashString0;
  const rfchar *mFlashString1;
  const rfchar *mFlashString2;
  const rfchar *mFlashString3;
  const rfchar *mFlashString4;
  String        mString0;
  String        mString1;
  String        mString2;
  String        mString3;
  String        mString4;
};

#endif // __INCLUDED_BB33D42E68CC11E6AA6E0021CC66E280
