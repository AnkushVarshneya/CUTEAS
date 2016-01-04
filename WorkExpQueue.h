//////////////////////////////////////////////////////////////////////////
// WORKEXPQUEUE
// Implements a singly linked list of work experience by applicant

#ifndef WORKEXPQUEUE_H
#define WORKEXPQUEUE_H

#include "Types.h"
#include "WorkExp.h"

class WorkExpQueue {
  friend class Manager;
  friend class SelectEntryUI;
  class Node{
    friend class WorkExpQueue;
    friend class Manager;
    friend class SelectEntryUI;
    private:
      WorkExp* data;
      Node*    next;
  };

  public:
    WorkExpQueue();
    WorkExpQueue(WorkExpQueue&);
    ~WorkExpQueue();

    void   pushBack(WorkExp*);
    bool   popFront();
    Node*  front();
    bool   remove(string, string, string, string);
    bool   empty();
    void   clear();
    int    size()  const;
    string print();

    WorkExp* getWork(string, string, string, string) const;
    
  private:
    Node* head;
};

#endif
