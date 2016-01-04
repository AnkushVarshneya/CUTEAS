//////////////////////////////////////////////////////////////////////////
// TACOURSEQUEUE
// Implements a singly linked list of courses TA'd by applicant

#ifndef TACOURSEQUEUE_H
#define TACOURSEQUEUE_H

#include "Types.h"
#include "TACourse.h"

class TACourse;

class TACourseQueue {
  friend class Manager;
  friend class SelectEntryUI;
  class Node{
    friend class TACourseQueue;
    friend class Manager;
    friend class SelectEntryUI;
    private:
      TACourse* data;
      Node*     next;
  };

  public:
    TACourseQueue();
    TACourseQueue(TACourseQueue&);
    ~TACourseQueue();

    void   pushBack(TACourse*);
    bool   popFront();
    Node*  front();
    bool   empty();
    void   clear();
    int    size()  const;
    string print();
    bool   remove(string, string, string, string);

    TACourse* getCourse(string, string, string, string) const;
    
  private:
    Node* head;
   
};

#endif
