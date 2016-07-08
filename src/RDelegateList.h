#ifndef __INCLUDED_8E00360044CF11E6804600F1F38F93EF
#define __INCLUDED_8E00360044CF11E6804600F1F38F93EF

#include <stddef.h>

template <class T>
struct RDelegateListNode {
  T data;

  RDelegateListNode<T> *next;

  RDelegateListNode() : next(NULL) {
  }

  RDelegateListNode(const T &value) : data(value), next(NULL) {
  }
};

template <typename T>
class RDelegateList {
protected:
  typedef RDelegateListNode<T> NodeType;

  NodeType *mRoot;

public:
  RDelegateList() : mRoot(NULL) {
  }

  ~RDelegateList() {
    clear();
  }

  bool
  insert(const T &value) {
    NodeType *node = new NodeType(value);

    if(mRoot != NULL) {
      node->next = mRoot;
    }

    mRoot = node;
  }

  void
  erase(const T &value) {
    if(mRoot == NULL) {
      return;
    }

    NodeType *node     = mRoot;
    NodeType *nodeNext = NULL;
    NodeType *nodePrev = NULL;

    for(; node != NULL; nodePrev = node, node = nodeNext) {
      nodeNext = node->next;

      if(node->data != value) {
        continue;
      }

      delete node;

      if(node == mRoot) {
        mRoot = nodeNext;
        node  = NULL;
      } else {
        nodePrev->next = nodeNext;
        node           = nodePrev;
      }
    }
  }

  void
  clear() {
    if(mRoot == NULL) {
      return;
    }

    NodeType *node     = mRoot;
    NodeType *nodeNext = NULL;

    for(; node != NULL; node = nodeNext) {
      nodeNext = node->next;

      delete node;
    }

    mRoot = NULL;
  }
};

#endif // #ifndef __INCLUDED_8E00360044CF11E6804600F1F38F93EF
