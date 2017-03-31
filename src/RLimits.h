#ifndef __INCLUDED_038A282615DF11E7AA6EA088B4D1658C
#define __INCLUDED_038A282615DF11E7AA6EA088B4D1658C

#include <limits>

#pragma GCC visibility push(default)

template <class T>
class RNumericLimits : public std::numeric_limits<T>
{
};

template <>
class RNumericLimits<bool> : public std::numeric_limits<bool>
{
public:
  typedef bool T;

  static const T sMin = false;
  static const T sMax = true;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<unsigned char> : public std::numeric_limits<unsigned char>
{
public:
  typedef unsigned char T;

  static const T sMin = 0;
  static const T sMax = UCHAR_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<signed char> : public std::numeric_limits<signed char>
{
public:
  typedef signed char T;

  static const T sMin = SCHAR_MIN;
  static const T sMax = SCHAR_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<char> : public std::numeric_limits<char>
{
public:
  typedef char T;

  static const T sMin = CHAR_MIN;
  static const T sMax = CHAR_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<unsigned short> : public std::numeric_limits<unsigned short>
{
public:
  typedef unsigned short T;

  static const T sMin = 0;
  static const T sMax = USHRT_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<signed short> : public std::numeric_limits<signed short>
{
public:
  typedef signed short T;

  static const T sMin = SHRT_MIN;
  static const T sMax = SHRT_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<unsigned int> : public std::numeric_limits<unsigned int>
{
public:
  typedef unsigned int T;

  static const T sMin = 0;
  static const T sMax = UINT_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<signed int> : public std::numeric_limits<signed int>
{
public:
  typedef signed int T;

  static const T sMin = INT_MIN;
  static const T sMax = INT_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<unsigned long int> : public std::numeric_limits<unsigned
                                                                     long int>
{
public:
  typedef unsigned long int T;

  static const T sMin = 0;
  static const T sMax = ULONG_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

template <>
class RNumericLimits<signed long int>: public std::numeric_limits<signed
                                                                  long int>
{
public:
  typedef signed long int T;

  static const T sMin = LONG_MIN;
  static const T sMax = LONG_MAX;

  // Floating point specific.
  static const T sEpsilon    = 0;
  static const T sRoundError = 0;
};

#pragma GCC visibility pop

#endif // __INCLUDED_038A282615DF11E7AA6EA088B4D1658C
