//////////////////////////////////////////////////////////////////////////
// COURSEQUEUE
// Implements a singly linked list of all courses

#ifndef COURSEQUEUE_H
#define COURSEQUEUE_H

#include "Types.h"
#include "Course.h"

class CourseQueue {
  friend ostream& operator<<(ostream&, CourseQueue&);
  friend class SelectCrsUI;
  friend class StuAppFormUI;
  friend class GradAppFormUI;
  friend class CourseInfoUI;
  friend class Manager;
  friend class TakenCourse;
  friend class OneReportUI;
  friend class AllReportsUI;
  friend class TACourse;
  friend class TakenCourseInfoUI;
  friend class TACourseInfoUI;
  class Node {
    friend class CourseQueue;
    friend class SelectCrsUI;
    friend class StuAppFormUI;
    friend class GradAppFormUI;
    friend class CourseInfoUI;
    friend class Manager;
    friend class TakenCourse;
    friend class OneReportUI;
    friend class AllReportsUI;
    friend class TACourse;
    friend class TakenCourseInfoUI;
    friend class TACourseInfoUI;
    private:
      Course* data;
      Node*   next;
  };

  public:
    CourseQueue();
    CourseQueue(CourseQueue&);
    ~CourseQueue();
    void  pushBack(Course*);
    bool  popFront();
    Node* front();
    bool  remove(string);
    bool  empty();
    void  clear();
    void  clearCopy();
    int   size()  const;
    void  print() const;

    Course*      operator[](int) const;
    CourseQueue& operator+=(Course*);
    CourseQueue& operator+=(CourseQueue&);
    CourseQueue  operator+ (Course*);
    CourseQueue  operator+ (CourseQueue&);
    CourseQueue& operator-=(Course*);
    CourseQueue& operator-=(CourseQueue&);
    CourseQueue  operator- (Course*);
    CourseQueue  operator- (CourseQueue&);
    void         operator!();

  private:
    Node* head;
};

#endif

