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
    Timer,
    User, ///< User defined events start from this value.
  };

  explicit
  REvent(const rcount &type=None);

  ~REvent();

  void
  accept();

  void
  ignore();

  bool
  isAccepted() const;

  void
  setAccepted(bool accepted);

  rcount
  type() const;
  static rcount
  registerEventType();

private:
  rcount mType;
  bool   mIsAccepted;
};

/**
 * An easy wrapper template for provide auto registered static type variable.
 * So that you could focus on the implementation of event class.
 */
template <class MyType, class BaseType>
class TypeRegisteredEvent : public BaseType
{
protected:
  typedef TypeRegisteredEvent<MyType, BaseType> RegisteredEventType;

public:
  // Inherit all constructors
  template <class ... ParamTypes>
  explicit
  TypeRegisteredEvent(ParamTypes ... params)
    : BaseType(params ...)
  {
  }

  static const rcount sType;
};

template <class MyType, class BaseType>
const rcount TypeRegisteredEvent<MyType,
                                 BaseType>::sType = REvent::registerEventType();

template <rcount TypeValue, class BaseType>
class TypeEnumeratedEvent : public BaseType
{
protected:
  typedef TypeEnumeratedEvent<TypeValue, BaseType> RegisteredEventType;

public:
  // Inherit all constructors
  template <class ... ParamTypes>
  explicit
  TypeEnumeratedEvent(ParamTypes ... params)
    : BaseType(params ...)
  {
  }

  static const rcount sType = TypeValue;
};

//template <rcount TypeValue, class BaseType>
//const rcount TypeEnumeratedEvent<TypeValue, BaseType>::sType = TypeValue;

template <class EventType, class ... ParamTypes>
EventType *
rMakeEvent(ParamTypes ... params)
{
  return new EventType(EventType::sType, params ...);
}

REvent *
rMakeEvent(const rcount &type);

#endif // __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
