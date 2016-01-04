/////////////////////////////////////////////////////////////////////////
// COURSE CLASS
// Contains all of the attributes and functions of a course

#ifndef COURSE_H
#define COURSE_H

#include "UGradAppQueue.h"
#include "GradAppQueue.h"

class Course {
  friend ostream& operator<<(ostream&,Course&);
  public:
    Course(string="");
    ~Course();

    string  getName();
    string  getTerm();
    string  getYear();

    void           setName(string);
    void           setTerm(string);
    void           setYear(string);
    UGradAppQueue* getUGradApps();
    GradAppQueue*  getGradApps();

  private:
    string         name;
    string         term;
    string         year;
    UGradAppQueue* UGradApps;
    GradAppQueue*  GradApps;
};

#endif
