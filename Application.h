/////////////////////////////////////////////////////////////////////////
// APPLICATION CLASS
// Contains all of the attributes and functions of an application

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Types.h"

class Course;
class TACourseQueue;
class WorkExpQueue;

enum Status { PENDING=0, ASSIGNED=1, CLOSED=2 };

class Application {
  public:
    Application();
    ~Application();

    Course*            getCourse()             const;
    Status             getStatus()             const;
    int                getAppNum()             const;
    string             getStatusString(Status) const;
    TACourseQueue*     getTACrsQueue()         const;
    WorkExpQueue*      getWorkExpQueue()       const;

    void   setCourse(Course*);
    void   setStatus(Status);
    void   setAppNum(int);
    void   setTACrsQueue(TACourseQueue*);
    void   setWorkExpQueue(WorkExpQueue*);
    void   print() const;
    Application& operator-();
    Application& operator+();

  private:
    Course*       course;
    Status        status;
    int           appNum;

    // Linked lists
    TACourseQueue*    tACrsQueue;
    WorkExpQueue*     workExp;   

};

#endif
