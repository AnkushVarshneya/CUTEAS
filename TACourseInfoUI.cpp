//////////////////////////////////////////////////////////////////////////
// TA COURSES INFORMATION WINDOW
// Prompts user to give more information about ta'd courses

#include <fstream>

#include "TACourseInfoUI.h"
#include "TakenCourseInfoUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "TACourseQueue.h"
#include "WorkExpUI.h"
#include "SelectEntryUI.h"
#include "GradAppFormUI.h"
#include "CourseQueue.h"


//////////////////////////////////////////////////////////////////////////
// Constructor
TACourseInfoUI::TACourseInfoUI(Manager* aManager, int prev, int type, UGradApp* app, TACourse* t)
: CourseInfoUI(aManager, prev, type, app),
  nextButton("Next"),
  courseButton("New Course"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;
  if (t) { // If a TACourse was passed in, assign it to ta
    ta = t;
    addCrs = FALSE;
  }
  else {   // Else make a new TACourse
    ta = new TACourse(manager);
    addCrs = TRUE;
  }
  initialize();
}

//////////////////////////////////////////////////////////////////////////
// Constructor
TACourseInfoUI::TACourseInfoUI(Manager* aManager, int prev, int type, GradApp* app, TACourse* t)
: CourseInfoUI(aManager, prev, type, app),
  nextButton("Next"),
  courseButton("New Course"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;
  if (t) { // If a TACourse was passed in, assign it to ta
    ta = t;
    addCrs = FALSE;
  }
  else {   // Else make a new TACourse
    ta = new TACourse(manager);
    addCrs = TRUE;
  }
  initialize();
}

//////////////////////////////////////////////////////////////////////////
// Destructor
TACourseInfoUI::~TACourseInfoUI() {
  //cout << "DESTRUCT TACourseInfoUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Initialize
//   Extension of the constructor
void TACourseInfoUI::initialize() {
  aLabel.set_text("Select a course TA'd for:");
  finalLabel.set_text("Supervisor: ");
  courseCombo.append("None");
  courseCombo.set_active(20);

  //Read from faculty file using getline function
  count = 0; 
  ifstream infile2("faculty.txt", ios::in);
  if (!infile2) {
    cout << "Could not open file" << endl;
  }
  while (!infile2.eof()) {
    getline(infile2, faculty[count]);
    count++;
  }
  for (i=0; i<(count); i++) 
    finalCombo.append(faculty[i]);
  finalCombo.set_active(0);

  // Set widgets if we are NOT adding (i.e. editing) a course
  if (!addCrs)
    setWidgets();

  if (prevWin != 3) { // If previous window was NOT from SelectEntryUI
    createTable.attach(backButton, 0, 1, 4, 5, Gtk::FILL,Gtk::FILL,5, 50); 
    createTable.attach(courseButton, 1, 2, 4, 5,Gtk::FILL,Gtk::FILL,8, 50);
    createTable.attach(nextButton, 2, 3, 4, 5, Gtk::FILL,Gtk::FILL,5, 50); 
  }
  else {
    createTable.attach(cancelButton, 0, 1, 4, 5, Gtk::FILL,Gtk::FILL,5, 50); 
    createTable.attach(saveButton, 2, 3, 4, 5, Gtk::FILL,Gtk::FILL,5, 50); 
  }

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TACourseInfoUI::on_nextButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TACourseInfoUI::on_backButton), "Back") );
  courseButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TACourseInfoUI::on_courseButton), "New Course") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TACourseInfoUI::on_saveButton), "Save") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TACourseInfoUI::on_cancelButton), "Cancel") );

  show_all_children();

  //cout << "CONSTRUCT TACourseInfoUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Sets the widgets to the correct selection
void TACourseInfoUI::setWidgets(){  
  string text;
  int i=0;

  text = ta->getName();
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();
  while (currNode != 0){ 
    if (currNode->data->getName() == text) {
      courseCombo.set_active(i);
      break;
    }
    i++;
    currNode = currNode->next;
  }

  text = ta->getTerm();
  for (i=0; i<MAX_BUF; i++){
    if(term[i] == text) {
      termCombo.set_active(i);
      break;
    }
  }

  text = ta->getYear();
  for (i=0; i<MAX_BUF; i++){
    if(year[i] == text) {
      yearCombo.set_active(i);
      break;
    }
  }

  text = ta->getSupervisor();
  for (i=0; i<MAX_BUF; i++){
    if(faculty[i] == text) {
      finalCombo.set_active(i);
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler of next button
void TACourseInfoUI::on_nextButton(const Glib::ustring& data){
  WorkExpUI* workExpWin;

  if (courseCombo.get_active_text() != "None") {
    ta->setName(courseCombo.get_active_text());
    ta->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text()); 
  }
  if (uApp != 0) {
    if (courseCombo.get_active_text() != "None")
      uApp->getTACrsQueue()->pushBack(ta);
    workExpWin = new WorkExpUI(manager, 0, 0, uApp, 0);
  }
  else {
    if (courseCombo.get_active_text() != "None")
      gApp->getTACrsQueue()->pushBack(ta);      
    workExpWin = new WorkExpUI(manager, 0, 1, gApp, 0);
  }

  workExpWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of back button
void TACourseInfoUI::on_backButton(const Glib::ustring& data){  
  // Clear queue
  if (uApp != 0) { 
    if (!(uApp->getTACrsQueue()->empty()));
      uApp->getTACrsQueue()->clear();
    TakenCourseInfoUI* takenCrsInfoWin = new TakenCourseInfoUI(manager, 2, 0, uApp, 0); 
    takenCrsInfoWin->show();
    delete this;
  }
  else {
    if (!(gApp->getTACrsQueue()->empty()));
      gApp->getTACrsQueue()->clear();
    manager->cancelApp();
    GradAppFormUI* gradFormWin = new GradAppFormUI(manager, 1, 0);
    gradFormWin->show();
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler of course button
void TACourseInfoUI::on_courseButton(const Glib::ustring& data){ 
  if (courseCombo.get_active_text() == "None") {
    Gtk::MessageDialog dialog(*this, "ERROR!"); 
    dialog.set_secondary_text("Please select a course"); 
    dialog.run();
    return;
  }

  TACourseInfoUI* taCrsInfoWin;

  ta->setName(courseCombo.get_active_text());
  ta->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());  
  if (uApp != 0) {
    uApp->getTACrsQueue()->pushBack(ta);
    taCrsInfoWin = new TACourseInfoUI(manager, 2, 0, uApp, 0);
  }
  else {
    gApp->getTACrsQueue()->pushBack(ta);
    taCrsInfoWin = new TACourseInfoUI(manager, 2, 1, gApp, 0);
  }

  taCrsInfoWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of cancel button
void TACourseInfoUI::on_cancelButton(const Glib::ustring& data){
  SelectEntryUI* selectEntryWin;

  if (uApp != 0)
    selectEntryWin = new SelectEntryUI(manager, 1, 0, uApp->getAppNum());
  else 
    selectEntryWin = new SelectEntryUI(manager, 1, 1, gApp->getAppNum());
  selectEntryWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of save button
void TACourseInfoUI::on_saveButton(const Glib::ustring& data){
  if (courseCombo.get_active_text() == "None") {
    Gtk::MessageDialog dialog(*this, "ERROR!"); 
    dialog.set_secondary_text("Please select a course"); 
    dialog.run();
    return;
  }

  SelectEntryUI* selectEntryWin; 

  ta->setName(courseCombo.get_active_text());
  ta->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());

  if (uApp != 0) {
    if (addCrs)
      uApp->getTACrsQueue()->pushBack(ta);
    selectEntryWin = new SelectEntryUI(manager, 1, 0, uApp->getAppNum());
  }
  else {
    if (addCrs) 
      gApp->getTACrsQueue()->pushBack(ta);
    selectEntryWin = new SelectEntryUI(manager, 1, 1, gApp->getAppNum());
  } 

  selectEntryWin->show();
  delete this;
}
