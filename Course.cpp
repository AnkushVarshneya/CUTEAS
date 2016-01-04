//////////////////////////////////////////////////////////////////////////
// COURSE CLASS
// Contains all of the attributes and functions of a course

#include "Course.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
Course::Course(string n) 
: name(n), UGradApps(new UGradAppQueue()), GradApps(new GradAppQueue())
{
  //cout << "CONSTRUCT Course : " << name << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Course::~Course() {
  //cout << "DESTRUCT Course " << name << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string         Course::getName()      { return name;      }
string         Course::getTerm()      { return term;      }
string         Course::getYear()      { return year;      }

UGradAppQueue* Course::getUGradApps() { return UGradApps; }
GradAppQueue*  Course::getGradApps()  { return GradApps;  }

//////////////////////////////////////////////////////////////////////////
// Set functions
void Course::setName(string n)    { name = n;       }
void Course::setTerm(string t)    { term = t;       }
void Course::setYear(string y)    { year = y;       }

//////////////////////////////////////////////////////////////////////////
// Overloaded << operator that prints out the current course
ostream& operator<<(ostream& out, Course& c) {
  out<< c.getName();
  return out;
}

