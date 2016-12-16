#ifndef __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
#define __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C

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

  virtual int
  type() const;
  static int
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
  int
  type() const
  {
    return sType;
  }

  static inline int
  staticType()
  {
    return sType;
  }

private:
  static const int sType;
};

template <class DerivedType, class BaseType>
const int TypeRegisteredEvent<DerivedType,
                              BaseType>::sType = REvent::registerEventType();

#endif // __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
