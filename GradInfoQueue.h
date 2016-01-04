//////////////////////////////////////////////////////////////////////////
// GRADINFO QUEUE
// Implements a singly linked list of all Graduate's Information

#ifndef GRADINFOQUEUE_H
#define GRADINFOQUEUE_H

#include "Types.h"
#include "Graduate.h"

class GradInfoQueue {
  friend class AppManager;
  class Node{
    friend class GradInfoQueue;
    friend class AppManager;
    private:
      Graduate* data;
      Node*   next;
  };

  public:
    GradInfoQueue();
    GradInfoQueue(GradInfoQueue&);
    ~GradInfoQueue();
    void  pushBack(Graduate*);
    bool  popFront();
    Node* front();
    bool  remove(string); 
    bool  empty();
    void  clear();
    int   size()  const;
    void  print() const;

    Graduate* isInQueue(string) const;
    
  private:
    Node* head;
   
};

#endif
