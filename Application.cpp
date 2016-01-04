//////////////////////////////////////////////////////////////////////////
// APPLICATION CLASS
// Contains all of the attributes and functions of an application

#include "Application.h"
#include "Types.h"
#include "TACourseQueue.h"
#include "WorkExpQueue.h"
#include "Course.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
Application::Application() {
  tACrsQueue     = new TACourseQueue();
  workExp        = new WorkExpQueue();
  //cout << "CONSTRUCT Application" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Application::~Application() {
  //cout << "DESTRUCT Application #" << appNum << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
Course*           Application::getCourse()       const { return course;        }
Status            Application::getStatus()       const { return status;        }
int               Application::getAppNum()       const { return appNum;        }
TACourseQueue*    Application::getTACrsQueue()   const { return tACrsQueue;    }
WorkExpQueue*     Application::getWorkExpQueue() const { return workExp;       }

string Application::getStatusString(Status stat) const  { 
  switch(stat) {
    case 0: return "PENDING";
    case 1: return "ASSIGNED";
    case 2: return "CLOSED";
  }
}

//////////////////////////////////////////////////////////////////////////
// Set functions
void Application::setStatus(Status stat)                  { status = stat;       }
void Application::setAppNum(int aNum)                     { appNum = aNum;       }
void Application::setCourse(Course* crs)                  { course = crs;        }
void Application::setTACrsQueue(TACourseQueue* tacq)      { tACrsQueue = tacq;   }
void Application::setWorkExpQueue(WorkExpQueue* weq)      { workExp = weq;       }


//////////////////////////////////////////////////////////////////////////
// Prints out an application
void Application::print() const {
  cout << "APPLICATION #: " << appNum << " for " << course->getName() 
       << " " << getStatusString(status) << endl;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded unary operators
Application& Application::operator-() {
  setStatus(CLOSED);
  return *this;
}

Application& Application::operator+() {
  setStatus(ASSIGNED);
  return *this;
}
