//////////////////////////////////////////////////////////////////////////
// GRADUATE CLASS
// Contains all the attributes and functions of a graduate student's information 

#ifndef GRADUATE_H
#define GRADUATE_H

#include "GenInfo.h"
#include "GradAppQueue.h"

class GenInfo;

class Graduate : public GenInfo {
  public:
    Graduate(string="000000000",string="",string="",string="",
             string="",string="",string="");
    ~Graduate();

    string        getResearch();
    string        getSupervisor();
    string        getProgram();
    GradAppQueue* getApps();

    void   setResearch(string);
    void   setSupervisor(string);
    void   setProgram(string);

    string print();

  private:
    string        researchArea;
    string        program;
    string        supervisor;
    GradAppQueue* apps;
};

#endif
