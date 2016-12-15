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

#endif // __INCLUDED_6FCA43F2953F11E6AA6EA088B4D1658C
