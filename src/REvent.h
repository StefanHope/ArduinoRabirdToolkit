#ifndef __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
#define __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C

#include <RTypes.h>
#include <RLimits.h>

class REvent
{
public:
  enum Type
  {
    None = RNumericLimits<rcount>::sMin,
    DeferredDelete,
    User, ///< User defined events start from this value.
  };

  REvent(rcount type=0);

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
  rcount mType;
  bool   mIsAccepted;
};

/**
 * An easy wrapper template for generate type() method and provide auto
 * registered static type variable. So that you could focus on the
 * implementation of event class.
 */
template <class BaseType = REvent>
class TypeRegisteredEvent : public BaseType
{
public:
  typedef TypeRegisteredEvent<BaseType> SelfType;

  // Inherit all constructors
  template <class ... ParamTypes>
  TypeRegisteredEvent(ParamTypes ... params)
    : BaseType(params ...)
  {
  }

  rcount
  type() const
  {
    return sType;
  }

  static const rcount sType;
};

template <class BaseType>
const rcount TypeRegisteredEvent<BaseType>::sType = REvent::registerEventType();

#endif // __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
