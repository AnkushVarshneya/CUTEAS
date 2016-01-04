//////////////////////////////////////////////////////////////////////////
// GENERFAL INFORMATION CLASS
// Contains all the attributes and functions of a student's information 

#ifndef GENINFO_H
#define GENINFO_H

#include "Types.h"

class GenInfo {
  public:
    GenInfo(string="000000000",string="",string="",string="");
    ~GenInfo();

    string getStuNum();
    string getFirstName();
    string getSurname();
    string getEmail();

    void   setStuNum(string);
    void   setFirstName(string);
    void   setSurname(string);
    void   setEmail(string);

  private:
    string stuNum;
    string firstName;
    string surname;
    string email; 
};

#endif
