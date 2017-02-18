#ifndef __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
#define __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C

#include <RTypes.h>

class REvent
{
public:
  REvent();

  virtual
  ~REvent();

  void
  accept();

  void
  ignore();

  bool
  isAccepted() const;

  void
  setAccepted(bool accepted);

  virtual rcount
  type() const;
  static rcount
  registerEventType();

private:
  bool mIsAccepted;
};

/**
 * An easy wrapper template for generate type() method and provide auto
 * registered static type variable. So that you could focus on the
 * implementation of event class.
 */
template <class DerivedType, class BaseType>
class TypeRegisteredEvent : public BaseType
{
public:
  rcount
  type() const
  {
    return sType;
  }

  static inline rcount
  staticType()
  {
    return sType;
  }

private:
  static const rcount sType;
};

template <class DerivedType, class BaseType>
const rcount TypeRegisteredEvent<DerivedType,
                                 BaseType>::sType = REvent::registerEventType();

#endif // __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
