/*
 *  Signal.h
 *  A lightweight signals and slots implementation using fast delegates
 *
 *  Created by Patrick Hogan on 5/18/09.
 *
 *
 *
 */

// 5/7/16 Hong-She Liang:
//  Renamed to RSignal.h for suitable for the library name.
//  Changed namespace to "RabirdToolkit"
//  Changed guarder macro

#ifndef __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
#define __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C

#include "RDelegate.h"
#include "RDelegateList.h"

namespace RabirdTookit {

template <class Param0 = void>
class RSignal0 {
public:
  typedef Delegate0<void> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)()) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)() const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)()) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)() const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit() const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))();
    }
  }

  void
  operator ()() const {
    emit();
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1>
class RSignal1 {
public:
  typedef Delegate1<Param1> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1);
    }
  }

  void
  operator ()(Param1 p1) const {
    emit(p1);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2>
class RSignal2 {
public:
  typedef Delegate2<Param1, Param2> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2) const {
    emit(p1, p2);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2, class Param3>
class RSignal3 {
public:
  typedef Delegate3<Param1, Param2, Param3> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2, Param3 p3) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2, p3);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2, Param3 p3) const {
    emit(p1, p2, p3);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2, class Param3, class Param4>
class RSignal4 {
public:
  typedef Delegate4<Param1, Param2, Param3, Param4> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3,
                                  Param4 p4) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj,
             void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3,
                                     Param4 p4) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2, p3, p4);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
    emit(p1, p2, p3, p4);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5>
class RSignal5 {
public:
  typedef Delegate5<Param1, Param2, Param3, Param4, Param5> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2, p3, p4, p5);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
    emit(p1, p2, p3, p4, p5);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5,
          class Param6>
class RSignal6 {
public:
  typedef Delegate6<Param1, Param2, Param3, Param4, Param5, Param6> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5, Param6 p6)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5, Param6 p6) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5, Param6 p6)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5, Param6 p6) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2, p3, p4, p5, p6);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5,
              Param6 p6) const {
    emit(p1, p2, p3, p4, p5, p6);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5,
          class Param6, class Param7>
class RSignal7 {
public:
  typedef Delegate7<Param1, Param2, Param3, Param4, Param5, Param6,
                    Param7> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5, Param6 p6, Param7 p7)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5, Param6 p6, Param7 p7) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5, Param6 p6, Param7 p7)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5, Param6 p6, Param7 p7) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6,
       Param7 p7) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2, p3, p4, p5, p6, p7);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6,
              Param7 p7) const {
    emit(p1, p2, p3, p4, p5, p6, p7);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5,
          class Param6, class Param7, class Param8>
class RSignal8 {
public:
  typedef Delegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7,
                    Param8> _Delegate;

private:
  typedef RDelegateList<_Delegate>              DelegateList;
  typedef typename DelegateList::const_iterator DelegateIterator;
  DelegateList mDelegateList;

public:
  void
  connect(_Delegate delegate) {
    mDelegateList.insert(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                  Param5 p5, Param6 p6, Param7 p7,
                                  Param8 p8) const) {
    mDelegateList.insert(MakeDelegate(obj, func));
  }

  void
  disconnect(_Delegate delegate) {
    mDelegateList.erase(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5, Param6 p6, Param7 p7,
                                     Param8 p8)) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4,
                                     Param5 p5, Param6 p6, Param7 p7,
                                     Param8 p8) const) {
    mDelegateList.erase(MakeDelegate(obj, func));
  }

  void
  clear() {
    mDelegateList.clear();
  }

  void
  emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6,
       Param7 p7, Param8 p8) const {
    for(DelegateIterator i = mDelegateList.begin(); i != mDelegateList.end();
        ) {
      (*(i++))(p1, p2, p3, p4, p5, p6, p7, p8);
    }
  }

  void
  operator ()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6,
              Param7 p7, Param8 p8) const {
    emit(p1, p2, p3, p4, p5, p6, p7, p8);
  }

  bool
  empty() const {
    return mDelegateList.empty();
  }
};
} // namespace

#endif //__INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
