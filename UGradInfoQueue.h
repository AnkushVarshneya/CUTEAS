//////////////////////////////////////////////////////////////////////////
// UGRADINFO QUEUE
// Implements a singly linked list of all Undergraduates

#ifndef UGRADINFOQUEUE_H
#define UGRADINFOQUEUE_H

#include "Types.h"
#include "Undergraduate.h"

class UGradInfoQueue {
  friend class Manager;

  class Node{
    friend class UGradInfoQueue;
    friend class Manager;
    private:
      Undergraduate* data;
      Node*          next;
  };

  public:
    UGradInfoQueue();
    UGradInfoQueue(UGradInfoQueue&);
    ~UGradInfoQueue();

    void  pushBack(Undergraduate*);
    bool  popFront();
    Node* front();
    bool  empty();
    bool  remove(string);  
    void  clear();
    int   size()  const;
    void  print() const;

    Undergraduate* isInQueue(string) const;
    
  private:
    Node* head;
};

#endif
