//////////////////////////////////////////////////////////////////////////
// WORKEXP CLASS
// Contains all of the attributes and functions of a work experience

#ifndef WORKEXP_H
#define WORKEXP_H

#include "Types.h"

class Manager;

class WorkExp {
  friend ostream& operator<<(ostream&,WorkExp&);
  public:
    WorkExp(Manager* = 0, string = "");
	WorkExp(WorkExp&);
    ~WorkExp();
   
    Manager* manager;

    string  getResp();
    string  getDuration();
    string  getStart();
    string  getEnd();
    bool    operator==(WorkExp*);  
	bool    operator!=(WorkExp*);
    void setResp(string);
    void setDataMembers(string, string, string);
	string print();

  private:
    string   resp;
    string   duration;
    string   start;
    string   end;
};

#endif

