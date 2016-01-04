//////////////////////////////////////////////////////////////////////////
// WORKEXP CLASS
// Contains all of the attributes and functions of a work experience

#include "Types.h"
#include "WorkExp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
WorkExp::WorkExp(Manager* aManager, string r) {
  manager = aManager;
  setResp(r);
  //cout << "CONSTRUCT WorkExp for " << r << endl;
}



//////////////////////////////////////////////////////////////////////////
//Copy constructor
WorkExp::WorkExp(WorkExp& aCopy){
	setResp(aCopy.getResp());
	setDataMembers(aCopy.getDuration(),aCopy.getStart(),aCopy.getEnd());
}
//////////////////////////////////////////////////////////////////////////
// Destructor
WorkExp::~WorkExp() {
 
}

//////////////////////////////////////////////////////////////////////////
// Operator == to test if two work experiences are the same 
bool WorkExp::operator==(WorkExp* compar){
	return((this->getResp() == compar->getResp())
		&& (this->getDuration() == compar->getDuration())
		&& (this->getStart() == compar->getStart())
		&& (this->getEnd() == compar->getEnd()));
}

//////////////////////////////////////////////////////////////////////////
// Operator != to test if two work experiences are the same 
bool WorkExp::operator!=(WorkExp* compar){
	return !(*this==compar);
}


//////////////////////////////////////////////////////////////////////////
// Get functions
string  WorkExp::getResp()         { return resp;     }
string  WorkExp::getDuration()     { return duration; }
string  WorkExp::getStart()        { return start;    }
string  WorkExp::getEnd()          { return end;      }

//////////////////////////////////////////////////////////////////////////
// Set functions
void WorkExp::setResp(string r)         { resp = r;       }

string WorkExp::print(){
	string out = "Responsibility: " + getResp() + "\n" +
               "     Duration: " + getDuration() + "\n" +
               "     Start: " + getStart() + "\n" +
               "     End: " + getEnd() + "\n";

    return out;
}
void WorkExp::setDataMembers(string dur, string s, string e) {
  duration = dur;
  start = s;
  end = e;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded << operator that prints out the current course
ostream& operator<<(ostream& out, WorkExp& c) {
  out<< c.getResp();
  return out;
}



