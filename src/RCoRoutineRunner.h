#ifndef __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C
#define __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C

#include <RTypes.h>
#include <pt/pt.h>

class RCoRoutineBasicRunner
{
public:
  RCoRoutineBasicRunner(void *impl);
  virtual
  ~RCoRoutineBasicRunner();

  virtual char
  run() = 0;

protected:
  void *
  _impl()
  {
    return mImpl;
  }

public:
  struct pt mPt;

private:
  friend class RCoRoutine;

  const void *mImpl;
};

template <class ImplementationType>
class RCoRoutineRunner : public RCoRoutineBasicRunner
{
protected:
  RCoRoutineRunner(ImplementationType *impl) : RCoRoutineBasicRunner(impl)
  {
  }

  // Provided rThis support
  inline ImplementationType *
  pImpl()
  {
    return static_cast<ImplementationType *>(_impl());
  }

  inline ImplementationType *
  pImpl() const
  {
    return static_cast<ImplementationType *>(_impl());
  }
};

#endif // __INCLUDED_ECE554E80AF211E7AA6EA088B4D1658C
