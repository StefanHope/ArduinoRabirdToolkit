#ifndef __INCLUDED_8E00360044CF11E6804600F1F38F93EF
#define __INCLUDED_8E00360044CF11E6804600F1F38F93EF

#include <stddef.h>
#include <memory>
#include <iterator>
#include <algorithm>

namespace Rt
{

template <class T, class Allocator = std::allocator<T> >
class RDelegateList
{
protected:
  class IteratorType;
  class NodeType;

public:
  typedef IteratorType iterator;
  typedef IteratorType const_iterator;

protected:
  NodeType *mRoot;

public:
  RDelegateList() : mRoot(NULL)
  {
  }

  ~RDelegateList()
  {
    clear();
  }

  bool
  insert(const T &value)
  {
    NodeType *node = new NodeType(value);

    if(mRoot != NULL)
    {
      node->mNext = mRoot;
    }

    mRoot = node;
  }

  void
  erase(const T &value)
  {
    if(mRoot == NULL)
    {
      return;
    }

    NodeType *node     = mRoot;
    NodeType *nodeNext = NULL;
    NodeType *nodePrev = NULL;

    for(; node != NULL; (nodePrev = node), (node = nodeNext))
    {
      nodeNext = node->mNext;

      if(node->data != value)
      {
        continue;
      }

      delete node;

      if(node == mRoot)
      {
        mRoot = nodeNext;
        node  = NULL;
      }
      else
      {
        nodePrev->mNext = nodeNext;
        node = nodePrev;
      }
    }
  }

  void
  clear()
  {
    if(mRoot == NULL)
    {
      return;
    }

    NodeType *node     = mRoot;
    NodeType *nodeNext = NULL;

    for(; node != NULL; node = nodeNext)
    {
      nodeNext = node->mNext;

      delete node;
    }

    mRoot = NULL;
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
};

// List node
template <class T, class Allocator>
class RDelegateList<T, Allocator>::NodeType
{
public:
  T         mValue;
  NodeType *mNext;

  NodeType() : mNext(NULL)
  {
  }

  NodeType(const T &value) : mValue(value), mNext(NULL)
  {
  }

  NodeType(const T &value, NodeType * next) : mValue(value), mNext(next)
  {
  }

  ~NodeType()
  {
  }
};

// List iterator
template <class T, class Allocator>
class RDelegateList<T, Allocator>::IteratorType
  : public std::iterator<
    std::forward_iterator_tag,
    T,
    typename Allocator::difference_type,
    typename Allocator::pointer,
    typename Allocator::reference
    >
{
private:
  typedef typename RDelegateList<T, Allocator>::NodeType NodeType;
  NodeType *mNode;

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
    return (mNode == right.mNode);
  }

  bool
  operator !=(const IteratorType &right) const
  {
    return (mNode != right.mNode);
  }

  IteratorType &
  operator ++()
  {
    mNode = mNode->mNext;
    return *this;
  }

  IteratorType
  operator ++(int)
  {
    IteratorType temp(mNode);

    mNode = mNode->mNext;
    return temp;
  }

  IteratorType &
  operator +=(unsigned int n)
  {
    for(unsigned int i = 0; i < n; ++i)
    {
      mNode = mNode->mNext;
    }

    return *this;
  }
};
}  // namespace

#endif // #ifndef __INCLUDED_8E00360044CF11E6804600F1F38F93EF
