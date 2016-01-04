//////////////////////////////////////////////////////////////////////////
// MANAGER FOR THE cuTAES SYSTEM
// Controls the system's applications and queues

#include <fstream>
#include <sstream>
#include <string>

#include "Manager.h"
#include "Tools.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradInfoQueue.h"
#include "GradInfoQueue.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "CourseQueue.h"
#include "TakenCourse.h"
#include "TACourseQueue.h"
#include "TACourse.h"
#include "WorkExpQueue.h"
#include "WorkExp.h"


//////////////////////////////////////////////////////////////////////////
// Default constructor
Manager::Manager() 
: currUGradApp(0),
  currGradApp(0),
  allUGradApps(new UGradAppQueue()),
  allGradApps(new GradAppQueue()),
  allCourses(new CourseQueue()),
  allUGradInfo(new UGradInfoQueue()),
  allGradInfo(new GradInfoQueue())
{
  // Get the last Application number
  string appNumber;
  ifstream infile("lastAppNum.txt", ios::in);
  if (!infile)
    cout<<"Could not open file"<<endl;
  infile >> appNumber;
  istringstream is(appNumber, istringstream::in);
  is >> lastAppNum;

  // Assemble the allCourses queue from reading in course names from a file
  string courses[MAX_BUF];
  int    count=0, i;
  ifstream infile2("courses.txt", ios::in);
  if (!infile2)
    cout << "Could not open file" << endl;
  while (!infile2.eof()) {
    getline(infile2, courses[count]);
    count++;
  }
  for (i=0; i<(count-1); i++) {
    Course* newCourse = new Course(courses[i]);
    allCourses->pushBack(newCourse);
  }

  // Assemble the application and information queues from existing applications
  assembleQueues();

  allUGradApps->print();
  allGradApps->print();
  allUGradInfo->print();
  allGradInfo->print();

  //cout << "CONSTRUCT Manager" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Manager::~Manager() {
  // Output last Application number to file
  ofstream outFile("lastAppNum.txt", ios::out);
  if (!outFile)
    cout << "Could not open file" << endl;
  outFile << lastAppNum << endl;

  // Save all applictions to permanent storage
  saveEverything();

  cout << endl << endl << "**Deleting allUGradApps" << endl;
  allUGradApps->clear(); // Delete data and nodes
  delete allUGradApps;   // Delete pointer to the queue

  cout << endl << endl << "**Deleting allGradApps" << endl;
  allGradApps->clear();  // Delete data and nodes
  delete allGradApps;    // Delete pointer to queue

  cout << endl << endl << "**Deleting allUGradInfo" << endl;
  delete allUGradInfo;

  cout << endl << endl << "**Deleting allGradInfo" << endl;
  delete allGradInfo;

  cout << endl << endl << "**Deleting allCourses" << endl;
  allCourses->clear();
  delete allCourses;

  //cout << "DESTRUCT Manager" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get Functions
CourseQueue*       Manager::getCourseQueue()   { return allCourses;    }
GradAppQueue*      Manager::getGradApps()      { return allGradApps;   }
UGradAppQueue*     Manager::getUGradApps()     { return allUGradApps;  }
GradInfoQueue*     Manager::getGradInfo()      { return allGradInfo;   }
UGradInfoQueue*    Manager::getUGradInfo()     { return allUGradInfo;  }
UGradApp*          Manager::getCurrUGradApp()  { return currUGradApp;  }
GradApp*           Manager::getCurrGradApp()   { return currGradApp;   }

//////////////////////////////////////////////////////////////////////////
// Sets both current applications to be null
void Manager::setCurrAppsNull() { 
  currUGradApp = 0;
  currGradApp  = 0;
}

//////////////////////////////////////////////////////////////////////////
// Creates a new Undergrad Application
UGradApp* Manager::makeNewUGradApp() {
  UGradApp* app = new UGradApp;
  app->setStatus(PENDING);
  app->setAppNum(++lastAppNum);
  currUGradApp = app;
  return app;
}

//////////////////////////////////////////////////////////////////////////
// Creates a new Grad Application
GradApp* Manager::makeNewGradApp() {
  GradApp* app = new GradApp;
  app->setStatus(PENDING);
  app->setAppNum(++lastAppNum);
  currGradApp = app;
  return app;
}

//////////////////////////////////////////////////////////////////////////
// Changes the undergrad Application's members
void Manager::changeUAppMem() {
  UGradApp* newApp = new UGradApp;
  newApp->setStatus(PENDING);
  newApp->setAppNum(++lastAppNum);
  newApp->setUndergrad(currUGradApp->getUndergrad());
  currUGradApp = newApp;
}

//////////////////////////////////////////////////////////////////////////
// Changes the grad Application's members
void Manager::changeGAppMem() {
  GradApp* newApp = new GradApp;
  newApp->setStatus(PENDING);
  newApp->setAppNum(++lastAppNum);
  newApp->setGrad(currGradApp->getGrad());
  currGradApp = newApp;
}

//////////////////////////////////////////////////////////////////////////
// Cancels the current working Application
// Used when user presses the 'Cancel' button the the midst of applying
void Manager::cancelApp() {
  string aStuNum;

  if (currUGradApp) {
    aStuNum = currUGradApp->getUndergrad()->getStuNum();
    delete currUGradApp->getTakenCrsQueue();
    delete currUGradApp->getTACrsQueue();
    delete currUGradApp->getWorkExpQueue();
    delete currUGradApp;
    currUGradApp = 0;
    if (!allUGradApps->isInQueue(aStuNum))
      allUGradInfo->remove(aStuNum);
    lastAppNum--;
  }
  else if (currGradApp){
    aStuNum = currGradApp->getGrad()->getStuNum();
    delete currGradApp->getTACrsQueue();
    delete currGradApp->getWorkExpQueue();
    delete currGradApp;
    currGradApp = 0;
    if (!allGradApps->isInQueue(aStuNum))
      allGradInfo->remove(aStuNum);
    lastAppNum--;
  }

  //cout << "lastAppNum = " << lastAppNum << endl;
}

//////////////////////////////////////////////////////////////////////////
// Saves the current working Application
// Adds the current application to the appropriate AppQueue in Manager
//   and in the course object
void Manager::saveApp() {
  // Find course selected in course queue
  CourseQueue::Node* currCrs = allCourses->front();

  // If it is a UGradApp
  if (currUGradApp) {
    // Add to AppQueue
    allUGradApps->pushBack(currUGradApp);
    currUGradApp->getUndergrad()->getApps()->pushBack(currUGradApp);

    while(currCrs != 0){
      if (currCrs->data->getName() == currUGradApp->getCourse()->getName())
        break;
      currCrs = currCrs->next;
    }
    // Add to AppQueue in course object
    currCrs->data->getUGradApps()->pushBack(currUGradApp);
  }

  // If it is a GradApp
  else if (currGradApp) {
    // Add to AppQueue
    allGradApps->pushBack(currGradApp);
    currGradApp->getGrad()->getApps()->pushBack(currGradApp);

    while(currCrs != 0){
      if (currCrs->data->getName() == currGradApp->getCourse()->getName())
        break;
      currCrs = currCrs->next;
    }
    // Add to AppQueue in course object
    currCrs->data->getGradApps()->pushBack(currGradApp);
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the course pointer in UGradApp to a course in the CourseQueue
void Manager::setCourse(UGradApp* app, string course) {
  CourseQueue::Node* currNode = allCourses->front();
  while (currNode != 0) {
    if (currNode->data->getName() == course) { 
      app->setCourse(currNode->data);
      break;
    }
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the course pointer in GradApp to a course in the CourseQueue
void Manager::setCourse(GradApp* app, string course) {
  CourseQueue::Node* currNode = allCourses->front();
  while (currNode != 0) {
    if (currNode->data->getName() == course) { 
      app->setCourse(currNode->data);
      break;
    }
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the Undergrad pointer to the appropriate Undergrad in allUGradInfo
// But if it is a new Undergrad, set the student number and add to allUGradInfo
// All other values are over-written
void Manager::setUGradInfo(string num, string fn, string sn, string em, 
                           string maj, int yr, float cg, float mgpa) {
  // If this Undergrad is in the queue, set the Undergrad pointer
  if (allUGradInfo->isInQueue(num)) {
    currUGradApp->setUndergrad(allUGradInfo->isInQueue(num));
  }
  // If this is a new Undergrad, set student number and add it to the allUGradInfo queue
  else {
    currUGradApp->getUndergrad()->setStuNum(num);
    allUGradInfo->pushBack(currUGradApp->getUndergrad());
  }

  // Overwrite values
  overwriteInfo(currUGradApp, fn, sn, em, maj, yr, cg, mgpa);
}

//////////////////////////////////////////////////////////////////////////
// Sets the Grad pointer to the appropriate Grad in allGradInfo
// But if it is a new Grad, set the student number and add to allGradInfo
// All other values are over-written
void Manager::setGradInfo(string num, string fn, string sn, string em, 
                          string res, string prog, string sup) {
  // If this Grad is in the queue, set the Grad pointer
  if (allGradInfo->isInQueue(num)) {
    currGradApp->setGrad(allGradInfo->isInQueue(num));
  }
  // If this is a new Grad, set the data members and add it to the allGradInfo queue
  else {
    currGradApp->getGrad()->setStuNum(num);
    allGradInfo->pushBack(currGradApp->getGrad());
  }

  // Overwrite values
  overwriteInfo(currGradApp, fn, sn, em, res, prog, sup);
}

//////////////////////////////////////////////////////////////////////////
// Overwrite the General Info of an Undergrad, given an application
void Manager::overwriteInfo(UGradApp* app, string fn, string sn, string em, 
                             string maj, int yr, float cg, float mgpa) {
  app->getUndergrad()->setFirstName(fn);
  app->getUndergrad()->setSurname(sn);
  app->getUndergrad()->setEmail(em);
  app->getUndergrad()->setMajor(maj);
  app->getUndergrad()->setYear(yr);
  app->getUndergrad()->setCGPA(cg);
  app->getUndergrad()->setMGPA(mgpa);
}

//////////////////////////////////////////////////////////////////////////
// Overwrite the General Info of an Undergrad, given an application
void Manager::overwriteInfo(GradApp* app, string fn, string sn, string em, 
                             string res, string prog, string sup) {
  app->getGrad()->setFirstName(fn);
  app->getGrad()->setSurname(sn);
  app->getGrad()->setEmail(em);
  app->getGrad()->setResearch(res);
  app->getGrad()->setProgram(prog);
  app->getGrad()->setSupervisor(sup);
}

//////////////////////////////////////////////////////////////////////////
// Assemble the application and information queues from existing applications
//   Opens the correct file for each course and reads in the applications
//   from that file. New Application objects are made, its values are set,
//   and they are added to the appropriate AppQueue.
//   This is done for both Undergrad and Grad Applications
void Manager::assembleQueues() {
  int crsQueueSize;
  CourseQueue::Node* currNode;
  string cn, text, t1, t2, t3;
  UGradApp* uApp;
  GradApp* gApp;

  // For each type of application
  // 0 = UGradApp; 1 = GradApp
  for (int gradType=0; gradType<2; gradType++) {
    // Reset variables
    crsQueueSize = allCourses->size();
    currNode = allCourses->front();

    // For each course
    for (int index=0; index<crsQueueSize; index++) {
      // Get correct file
      if (gradType == 0)
        cn = "./Applications/UndergradApps/" + currNode->data->getName();
      else if (gradType == 1)
        cn = "./Applications/GradApps/" + currNode->data->getName();

      // Open file to import information
      ifstream infile3(cn.c_str(), ios::in);
      if (!infile3) {
        if (index < crsQueueSize-1)
          currNode = currNode->next;
        continue;
      }

      // While there is still another line to read in the file
      while (!infile3.eof()) {
        getline(infile3, text);

        // If it's the beginning of a UGrad Application
        if (text == "*NEW UGRAD APPLICATION*") {
          uApp = new UGradApp();
          for (int i=0; i<11; i++) {
            getline(infile3, text);
            switch (i) {
              case 0:  uApp->setAppNum(Tools::stringToInt(text)); break;
              case 1:  setCourse(uApp, text); break;
              case 2:  if (text == "PENDING")       uApp->setStatus(PENDING);
                       else if (text == "ASSIGNED") uApp->setStatus(ASSIGNED);
                       else if (text == "CLOSED")   uApp->setStatus(CLOSED);
                       break;
              case 3:  if (allUGradInfo->isInQueue(text)) {
                         uApp->setUndergrad(allUGradInfo->isInQueue(text));
                         while (i<11) {
                           getline(infile3, text);
                           i++;
                         }
                       }
                       else 
                         uApp->getUndergrad()->setStuNum(text);
                       break;
              case 4:  uApp->getUndergrad()->setFirstName(text); break;
              case 5:  uApp->getUndergrad()->setSurname(text); break;
              case 6:  uApp->getUndergrad()->setEmail(text); break;
              case 7:  uApp->getUndergrad()->setMajor(text); break;
              case 8:  uApp->getUndergrad()->setYear(Tools::stringToInt(text)); break;
              case 9:  uApp->getUndergrad()->setCGPA(Tools::stringToFloat(text)); break;
              case 10: uApp->getUndergrad()->setMGPA(Tools::stringToFloat(text)); 
                       allUGradInfo->pushBack(uApp->getUndergrad()); 
                       break;
            }
          }
          allUGradApps->pushBack(uApp);
          currNode->data->getUGradApps()->pushBack(uApp);
          uApp->getUndergrad()->getApps()->pushBack(uApp);
        }

        // If it's the beginning of a Grad Application
        else if (text == "*NEW GRAD APPLICATION*") {
          gApp = new GradApp();
          for (int i=0; i<10; i++) {
            getline(infile3, text);
            switch (i) {
              case 0:  gApp->setAppNum(Tools::stringToInt(text)); break;
              case 1:  setCourse(gApp, text); break;
              case 2:  if (text == "PENDING")       gApp->setStatus(PENDING);
                       else if (text == "ASSIGNED") gApp->setStatus(ASSIGNED);
                       else if (text == "CLOSED")   gApp->setStatus(CLOSED);
                       break;
              case 3:  if (allGradInfo->isInQueue(text)) {
                         gApp->setGrad(allGradInfo->isInQueue(text));
                         while (i<10) {
                           getline(infile3, text);
                           i++;
                         }
                       }
                       else 
                         gApp->getGrad()->setStuNum(text);
                       break;
              case 4:  gApp->getGrad()->setFirstName(text); break;
              case 5:  gApp->getGrad()->setSurname(text); break;
              case 6:  gApp->getGrad()->setEmail(text); break;
              case 7:  gApp->getGrad()->setResearch(text); break;
              case 8:  gApp->getGrad()->setProgram(text); break;
              case 9:  gApp->getGrad()->setSupervisor(text);
                       allGradInfo->pushBack(gApp->getGrad()); 
                       break;
            }
          }
          allGradApps->pushBack(gApp);
          currNode->data->getGradApps()->pushBack(gApp);
          gApp->getGrad()->getApps()->pushBack(gApp);
        }

        // If we are reading in the related courses (ONLY FOR UGRAD)
        if (text == "Related courses taken:") {
          getline(infile3, text);
          while (text != "") {
            TakenCourse* tknCrs = new TakenCourse(this, text);
            getline(infile3, t1);
            getline(infile3, t2);
            getline(infile3, t3);
            tknCrs->setDataMembers(t1, t2, t3);
            uApp->getTakenCrsQueue()->pushBack(tknCrs);
            getline(infile3, text);
          }
        }

        // If we are reading in the TA'd courses
        if (text == "TA courses taken:") {
          getline(infile3, text);
          while (text != "") {
            TACourse* taCrs = new TACourse(this, text);
            getline(infile3, t1);
            getline(infile3, t2);
            getline(infile3, t3);
            taCrs->setDataMembers(t1, t2, t3);
            if (gradType == 0)
              uApp->getTACrsQueue()->pushBack(taCrs);
            else
              gApp->getTACrsQueue()->pushBack(taCrs);
            getline(infile3, text);
          }
        }
    
        // If we are reading in the work experiences
        else if (text == "Work Experience:") {
          getline(infile3, text);
          while (text != "") {
            WorkExp* wrkExp = new WorkExp(this, text);
            getline(infile3, t1);
            getline(infile3, t2);
            getline(infile3, t3);
            wrkExp->setDataMembers(t1, t2, t3);
            if (gradType == 0)
              uApp->getWorkExpQueue()->pushBack(wrkExp);
            else
              gApp->getWorkExpQueue()->pushBack(wrkExp);
            getline(infile3, text);
          }
        }
      } 
      currNode = currNode->next;
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Saves all of the applications to permanent storage
//   For each course, opens a file in the UndergradApps and in the 
//   GradApps directories. For each application of that course, its information
//   is outputted into the file.
//   NOTE: There is a file for each course, even if there are no applications
//         for that course.
void Manager::saveEverything() {
  string cn;
  UGradAppQueue::Node* uAppNode;
  GradAppQueue::Node*  gAppNode;
  Queue<TakenCourse>::Node<TakenCourse>* takenNode;
  TACourseQueue::Node* taNode;
  WorkExpQueue::Node* workNode;
  ofstream outFile;

  // Get course queue
  CourseQueue::Node* currCrs = allCourses->front();

  while (currCrs != 0) {
    // UNDERGRADUATE APPLICATIONS
    // Open the appropriate course file
    cn = "./Applications/UndergradApps/" + currCrs->data->getName();
    outFile.open(cn.c_str(), ios::out); 
    if (!outFile)
      cout << "Could not open file" << endl;

    uAppNode  = currCrs->data->getUGradApps()->front();
    if (uAppNode != 0) {
      takenNode = uAppNode->data->getTakenCrsQueue()->front();
      taNode    = uAppNode->data->getTACrsQueue()->front();
      workNode  = uAppNode->data->getWorkExpQueue()->front();
    }
    while (uAppNode != 0) {
      // Output application information to permanent storage
      outFile << endl;
      outFile << "*NEW UGRAD APPLICATION*" << endl;
      outFile << uAppNode->data->getAppNum() << endl;
      outFile << uAppNode->data->getCourse()->getName() << endl;
      outFile << uAppNode->data->getStatusString(uAppNode->data->getStatus()) << endl;
      outFile << uAppNode->data->getUndergrad()->getStuNum() << endl;
      outFile << uAppNode->data->getUndergrad()->getFirstName() << endl;
      outFile << uAppNode->data->getUndergrad()->getSurname() << endl;
      outFile << uAppNode->data->getUndergrad()->getEmail() << endl;
      outFile << uAppNode->data->getUndergrad()->getMajor() << endl;
      outFile << uAppNode->data->getUndergrad()->getYear() << endl;
      outFile << uAppNode->data->getUndergrad()->getCGPA() << endl;
      outFile << uAppNode->data->getUndergrad()->getMGPA() << endl;

      outFile << endl;
      outFile << "Related courses taken:" << endl;
      while (takenNode != 0) {
         outFile << takenNode->data->getName() << endl;
         outFile << takenNode->data->getTerm() << endl;
         outFile << takenNode->data->getYear() << endl;
         outFile << takenNode->data->getFinalGrade() << endl;
         takenNode = takenNode->next;
      } 

      outFile << endl;
      outFile << "TA courses taken:" << endl;
      while (taNode != 0) {
         outFile << taNode->data->getName() << endl;
         outFile << taNode->data->getTerm()<< endl;
         outFile << taNode->data->getYear()<< endl;
         outFile << taNode->data->getSupervisor()<< endl;
         taNode = taNode->next;
      }

      outFile << endl;
      outFile << "Work Experience:" << endl;
      while (workNode != 0) {
         outFile << workNode->data->getResp() << endl;
         outFile << workNode->data->getDuration() << endl;
         outFile << workNode->data->getStart() << endl;
         outFile << workNode->data->getEnd() << endl;
         workNode = workNode->next;
      }

      uAppNode = uAppNode->next;
    }
    outFile.close();


    // GRADUATE APPLICATIONS
    // Open the appropriate course file
    cn = "./Applications/GradApps/" + currCrs->data->getName();
    outFile.open(cn.c_str(), ios::out); 
    if (!outFile)
      cout << "Could not open file" << endl;

    gAppNode = currCrs->data->getGradApps()->front();
    if (gAppNode != 0) {
      taNode   = gAppNode->data->getTACrsQueue()->front();
      workNode = gAppNode->data->getWorkExpQueue()->front();
    }
    while (gAppNode != 0) {
      // Output application information to permanent storage
      outFile << endl;
      outFile << "*NEW GRAD APPLICATION*" << endl;
      outFile << gAppNode->data->getAppNum() << endl;
      outFile << gAppNode->data->getCourse()->getName() << endl;
      outFile << gAppNode->data->getStatusString(gAppNode->data->getStatus()) << endl;
      outFile << gAppNode->data->getGrad()->getStuNum() << endl;
      outFile << gAppNode->data->getGrad()->getFirstName() << endl;
      outFile << gAppNode->data->getGrad()->getSurname() << endl;
      outFile << gAppNode->data->getGrad()->getEmail() << endl;
      outFile << gAppNode->data->getGrad()->getResearch() << endl;
      outFile << gAppNode->data->getGrad()->getProgram() << endl;
      outFile << gAppNode->data->getGrad()->getSupervisor() << endl;

      outFile << endl;
      outFile << "TA courses taken:" << endl;
      while (taNode != 0) {
         outFile << taNode->data->getName() << endl;
         outFile << taNode->data->getTerm()<< endl;
         outFile << taNode->data->getYear()<< endl;
         outFile << taNode->data->getSupervisor()<< endl;
         taNode = taNode->next;
      }

      outFile << endl;
      outFile << "Work Experience:" << endl;
      while (workNode != 0) {
         outFile << workNode->data->getResp() << endl;
         outFile << workNode->data->getDuration() << endl;
         outFile << workNode->data->getStart() << endl;
         outFile << workNode->data->getEnd() << endl;
         workNode = workNode->next;
      }

      gAppNode = gAppNode->next;
    }
    outFile.close();

    currCrs = currCrs->next;
  }
}


