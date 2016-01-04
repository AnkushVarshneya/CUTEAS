//////////////////////////////////////////////////////////////////////////
// GRADUATE CLASS
// Contains all the attributes and functions of a graduate student's information 

#include "Types.h"
#include "Graduate.h"

//////////////////////////////////////////////////////////////////////////
// Default Constructor
Graduate::Graduate(string num, string fn, string sn, string em,
                   string ra, string prg, string sup) 
     : GenInfo(num, fn, sn, em), researchArea(ra), program(prg), supervisor(sup),
       apps(new GradAppQueue())
{
  //cout << "CONSTRUCT Graduate" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Graduate::~Graduate() {
  //cout << "DESTRUCT Graduate StuNum #" << getStuNum() << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string Graduate::getResearch()    { return researchArea; }
string Graduate::getProgram()     { return program;      }
string Graduate::getSupervisor()  { return supervisor;   }
GradAppQueue* Graduate::getApps() { return apps; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void Graduate::setResearch(string ra)    { researchArea  = ra;  }
void Graduate::setProgram(string prg)    { program       = prg; }
void Graduate::setSupervisor(string sup) { supervisor    = sup; }

//////////////////////////////////////////////////////////////////////////
// Print function
string Graduate::print() { 
  string out = "Student Number: " + getStuNum() + "\n" +
               "Student Name: " + getFirstName() + " " + getSurname() + "\n" +
               "Email: " + getEmail() + "\n" +
               "Research: " + getResearch() + "\n" +
               "Supervisor: " + getSupervisor() + "\n" +
               "Program: " + getProgram();

  return out;
}
