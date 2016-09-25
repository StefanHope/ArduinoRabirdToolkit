#ifndef __INCLUDED_8E00360044CF11E6804600F1F38F93EF
#define __INCLUDED_8E00360044CF11E6804600F1F38F93EF

#include <stddef.h>
#include <memory>
#include <iterator>
#include <algorithm>

template <class T, class Allocator = std::allocator<T> >
class RForwardList
{
protected:
  class IteratorType;
  class NodeType;

public:
  typedef IteratorType iterator;
  typedef IteratorType const_iterator;

public:
  RForwardList() : mRoot(NULL)
  {
  }

  ~RForwardList()
  {
    clear();
  }

  iterator
  beforeBegin()
  {
    return iterator(reinterpret_cast<NodeType *>(&mRoot));
  }

  const_iterator
  beforeBegin() const
  {
    return const_iterator(reinterpret_cast<NodeType *>(&mRoot));
  }

  iterator
  eraseAfter(const_iterator position)
  {
    auto wantErasePosition = position + 1;

    if(wantErasePosition.mNode)
    {
      position.mNode->mNext = wantErasePosition.mNode->mNext;
      delete wantErasePosition.mNode;

      return iterator(position.mNode->mNext);
    }

    return end();
  }

  iterator
  eraseAfter(const_iterator position, const_iterator last)
  {
    auto currentPosition = position;

    while(currentPosition != last)
    {
      currentPosition = eraseAfter(position);
    }

    return last;
  }

  void
  pushFront(const T &value)
  {
    insertAfter(beforeBegin(), value);
  }

  iterator
  insertAfter(const_iterator position, const T &value)
  {
    if(position.mNode)
    {
      NodeType *node = new NodeType(value);

      node->mNext           = position.mNode->mNext;
      position.mNode->mNext = node;
    }
    else
    {
      return position;
    }
  }

  void
  remove(const T &value)
  {
    if(empty())
    {
      return;
    }

    auto it     = beforeBegin();
    auto nextIt = it;

    for(; it != end(); it = nextIt)
    {
      nextIt = it + 1;

      if(*nextIt == value)
      {
        nextIt = eraseAfter(it);
      }
    }
  }

  void
  clear()
  {
    if(empty())
    {
      return;
    }

    eraseAfter(beforeBegin(), end());
  }

  bool
  empty() const
  {
    return (mRoot == NULL);
  }

  iterator
  begin()
  {
    return iterator(mRoot);
  }

  iterator
  end()
  {
    return iterator();
  }

  const_iterator
  begin() const
  {
    return const_iterator(mRoot);
  }

  const_iterator
  end() const
  {
    return const_iterator();
  }

protected:
  NodeType *mRoot;
};

// List node
template <class T, class Allocator>
class RForwardList<T, Allocator>::NodeType
{
public:
  NodeType() : mNext(NULL)
  {
  }

  NodeType(const T &value) : mNext(NULL), mValue(value)
  {
  }

  NodeType(const T &value, NodeType * next) : mNext(next), mValue(value)
  {
  }

  ~NodeType()
  {
  }

public:
  NodeType *mNext;
  T         mValue;
};

// List iterator
template <class T, class Allocator>
class RForwardList<T, Allocator>::IteratorType
  : public std::iterator<
    std::forward_iterator_tag,
    T,
    typename Allocator::difference_type,
    typename Allocator::pointer,
    typename Allocator::reference
    >
{
private:
  typedef RForwardList<T, Allocator>  ListType;
  typedef typename ListType::NodeType NodeType;

public:
  IteratorType() : mNode(NULL)
  {
  }

  IteratorType(NodeType * n) : mNode(n)
  {
  }

  IteratorType(const IteratorType &l) : mNode(l.mNode)
  {
  }

  ~IteratorType()
  {
  }

  IteratorType &
  operator =(const IteratorType &right)
  {
    mNode = right.mNode;
    return *this;
  }

  T &
  operator *()
  {
    return mNode->mValue;
  }

  T *
  operator ->()
  {
    return &mNode->mValue;
  }

  const T &
  operator *() const
  {
    return mNode->mValue;
  }

  const T *
  operator ->() const
  {
    return &mNode->mValue;
  }

  bool
  operator ==(const IteratorType &right) const
  {
    return mNode == right.mNode;
  }

  bool
  operator !=(const IteratorType &right) const
  {
    return (mNode != right.mNode);
  }

  IteratorType &
  operator ++()
  {
    if(mNode)
    {
      mNode = mNode->mNext;
    }

    return *this;
  }

  IteratorType
  operator ++(int)
  {
    IteratorType temp(mNode);

    if(mNode)
    {
      mNode = mNode->mNext;
    }

    return temp;
  }

  IteratorType &
  operator +=(unsigned int n)
  {
    for(unsigned int i = 0; i < n; ++i)
    {
      if(mNode)
      {
        mNode = mNode->mNext;
      }
      else
      {
        break;
      }
    }

    return *this;
  }

  IteratorType
  operator +(unsigned int n)
  {
    IteratorType otherIt = *this;

    otherIt += n;

    return otherIt;
  }

private:
  NodeType *mNode;

  friend ListType;
};

#endif // #ifndef __INCLUDED_8E00360044CF11E6804600F1F38F93EF
