//////////////////////////////////////////////////////////////////////////
// UNDERGRAD APPLICATION CLASS
// Contains all of the attributes and functions of an undergraduate's application

#include "Types.h"
#include "UGradApp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
UGradApp::UGradApp() 
     : Application()
{
  undergrad      = new Undergraduate();
  takenCrsQueue  = new Queue<TakenCourse>();
  //cout << "CONSTRUCT UndergradApp" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
UGradApp::~UGradApp() {
  //cout << "DESTRUCT UndergradApp #" << getAppNum() << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
Undergraduate*    UGradApp::getUndergrad()     const { return undergrad;     }
Queue<TakenCourse>* UGradApp::getTakenCrsQueue() const { return takenCrsQueue; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void UGradApp::setUndergrad(Undergraduate* under)      { undergrad = under;   }
void UGradApp::setTakenCrsQueue(Queue<TakenCourse>* tcq) { takenCrsQueue = tcq; }

//////////////////////////////////////////////////////////////////////////
// Prints out an application
void UGradApp::print() const {
  cout << "APPLICATION #: " << getAppNum() << " for " << getCourse()->getName() 
       << " " << getStatusString(getStatus()) << endl;
}

