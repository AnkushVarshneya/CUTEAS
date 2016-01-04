//////////////////////////////////////////////////////////////////////////
// GRAD APPLICATION CLASS
// Contains all of the attributes and functions of a graduate's application

#include "GradApp.h"
#include "Course.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
GradApp::GradApp() 
: Application()
{
  grad = new Graduate();
  //cout << "CONSTRUCT GradApp" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
GradApp::~GradApp() {
  //cout << "DESTRUCT GradApp #" << getAppNum() << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
Graduate*    GradApp::getGrad() const { return grad; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void GradApp::setGrad(Graduate* gr) { grad = gr; }

//////////////////////////////////////////////////////////////////////////
// Prints out an application
void GradApp::print() const {
  cout << "APPLICATION #: " << getAppNum() << " for " << getCourse()->getName() 
       << " " << getStatusString(getStatus()) << endl;
}

