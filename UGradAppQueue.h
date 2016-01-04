//////////////////////////////////////////////////////////////////////////
// UNDERGRADUATE APPLICATION QUEUE
// Implements a singly linked list of all undergraduate applications

#ifndef UGRADAPPQUEUE_H
#define UGRADAPPQUEUE_H

#include "Types.h"

class UGradApp;

class UGradAppQueue {
  friend class OneReportUI;
  friend class AllReportsUI;
  friend class SelectAppUI;
  friend class Manager;
  class Node{
    friend class UGradAppQueue;
    friend class OneReportUI;
    friend class AllReportsUI;
    friend class SelectAppUI;
    friend class Manager;
    private:
      UGradApp*  data;
      Node*      next;
  };

  public:
    UGradAppQueue();
    UGradAppQueue(UGradAppQueue&);
    ~UGradAppQueue();

    void  pushBack(UGradApp*);
    bool  popFront();
    Node* front();
    bool  empty();
    void  clear();
    void  clearCopy();
    int   size()  const;
    void  print() const;

    void      sortByMGPA();
    bool      isInQueue(string) const;
    string    isAppNumInQueue(int);
    void      closeOtherUGrad(string, int);
    UGradApp* getApp(int) const;
    
  private:
    Node* head;
   
};

#endif

