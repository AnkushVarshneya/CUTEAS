//////////////////////////////////////////////////////////////////////////
// GRADUATE APPLICATION QUEUE
// Implements a singly linked list of all graduate applications

#ifndef GRADAPPQUEUE_H
#define GRADAPPQUEUE_H

#include "Types.h"

class GradApp;

class GradAppQueue {
  friend class OneReportUI;
  friend class AllReportsUI;
  friend class SelectAppUI;
  friend class Manager;
  class Node{
    friend class GradAppQueue;
    friend class OneReportUI;
    friend class AllReportsUI;
    friend class SelectAppUI;
    friend class Manager;
    private:
      GradApp*   data;
      Node*      next;
  };

  public:
    GradAppQueue();
    GradAppQueue(GradAppQueue&);
    ~GradAppQueue();
    void  pushBack(GradApp*);
    bool  popFront();
    Node* front();
    bool  empty();
    void  clear();
    void  clearCopy();
    int   size()  const;
    void  print() const;

    void     sortByResearch();
    bool     isInQueue(string) const;  
    string   isAppNumInQueue(int);
    void     closeOtherGrad(string, int);
    GradApp* getApp(int) const;
  
  private:
    Node* head;
   
};

#endif

