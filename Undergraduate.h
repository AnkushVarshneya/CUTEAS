//////////////////////////////////////////////////////////////////////////
// UNDERGRADUATE CLASS
// Contains all the attributes and functions of an undergraduate student's information 

#ifndef UNDERGRADUATE_H
#define UNDERGRADUATE_H

#include "GenInfo.h"
#include "UGradAppQueue.h"

class Undergraduate : public GenInfo {
  public:
    Undergraduate(string="000000000",string="",string="",string="",
		        string="",int=0,float=0.0,float=0.0);
   ~Undergraduate();

   string getMajor();
   int    getYear();
   float  getCGPA();
   float  getMGPA();
   UGradAppQueue* getApps();

   void   setMajor(string);
   void   setYear(int);
   void   setCGPA(float);
   void   setMGPA(float);

   string print();

  private:
    string   major;
    int      yearStanding;
    float    cgpa;
    float    majorGPA;
    UGradAppQueue* apps;
};

#endif
