//////////////////////////////////////////////////////////////////////////
// TAKEN COURSE QUEUE
// Implements a singly linked list of courses taken by applicant

#ifndef TAKENCOURSEQUEUE_H
#define TAKENCOURSEQUEUE_H

#include "Types.h"
#include "TakenCourse.h"

class TakenCourseQueue {
  friend class Manager;
  friend class SelectEntryUI;
  class Node{
    friend class TakenCourseQueue;
    friend class SelectEntryUI;
    private:
      friend class Manager;
      TakenCourse* data;
      Node*   next;
  };

  public:
    TakenCourseQueue();
    TakenCourseQueue(TakenCourseQueue&);
    ~TakenCourseQueue();

    void   pushBack(TakenCourse*);
    bool   popFront();
    Node*  front();
    bool   empty();
    void   clear();
    int    size()  const;
    string print();
    bool   remove(string, string, string, string);

    TakenCourse* getCourse(string, string, string, string) const;
    
  private:
    Node* head;
};

#endif

