/////////////////////////////////////////////////////////////////////////
// TAKENCOURSE CLASS
// Contains all of the attributes and functions of a taken course

#ifndef TAKENCOURSE_H
#define TAKENCOURSE_H

#include "Course.h"

class Course;
class Manager;

class TakenCourse : public Course {
  public:
    TakenCourse(Manager*, string="");
    ~TakenCourse();
   
    Manager* manager;

    string  getFinalGrade();
    void    setDataMembers(string, string, string);
    void    setCourse(string);
	bool    operator==(TakenCourse*);  
	bool    operator!=(TakenCourse*);
    string print();

  private:
    string finalGrade;
};

#endif
