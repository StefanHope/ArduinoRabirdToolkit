#ifndef __INCLUDED_CB5671DA425011E6932B00F1F38F93EF
#define __INCLUDED_CB5671DA425011E6932B00F1F38F93EF

#include "RGlobal.h"
#include "RRawPointer.h"
#include <Print.h>
#include <Printable.h>

class REvent;
class RThread;
class RObject : protected Printable
{
public:
  explicit
  RObject(RThread *targetThread);

public:
  RObject();

  virtual
  ~RObject();

  size_t
  printTo(Print&p) const;

  virtual bool
  event(REvent *e);
  RThread *
  thread() const;

  void
  moveToThread(RThread *targetThread);

  void
  deleteLater();

private:
#if !defined(R_OS_NONOS)
  RRawPointer<RThread> mThread;
#endif // #if !defined(R_OS_NONOS)

  friend RThread;
};

#endif // __INCLUDED_CB5671DA425011E6932B00F1F38F93EF
