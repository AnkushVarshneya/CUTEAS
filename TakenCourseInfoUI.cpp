//////////////////////////////////////////////////////////////////////////
// TAKEN COURSES INFORMATION WINDOW
// Prompts user to give more information about taken courses

#include <fstream>

#include "TakenCourseInfoUI.h"
#include "UGradApp.h"
#include "StuAppFormUI.h"
#include "TakenCourseInfoUI.h"
#include "TACourseInfoUI.h"
#include "SelectEntryUI.h"
#include "CourseQueue.h"


//////////////////////////////////////////////////////////////////////////
// Constructor
TakenCourseInfoUI::TakenCourseInfoUI(Manager* aManager, int prev, int type, UGradApp* app, TakenCourse* t)
: CourseInfoUI(aManager, prev, type, app),
  nextButton("Next"),
  courseButton("New Course"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;
  if (t) { // If a TakenCourse was passed in, assign it to taken
    taken = t;  
    addCrs = FALSE;
  }
  else {   // Else make a new TakenCourse to add
    taken = new TakenCourse(manager);
    addCrs = TRUE;
  }

  aLabel.set_text("Select a related course taken:");
  finalLabel.set_text("Final Grade: ");

  int j;
  for(i= i+1, j=0; i<(count-1); i++, j++) {
    finalCombo.append(info[i]);
    final[j] = info[i];
  }
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
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TakenCourseInfoUI::on_nextButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TakenCourseInfoUI::on_backButton), "Back") );
  courseButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TakenCourseInfoUI::on_courseButton), "New Course") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TakenCourseInfoUI::on_saveButton), "Save") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &TakenCourseInfoUI::on_cancelButton), "Cancel") );

  show_all_children();

  //cout << "CONSTRUCT TakenCourseInfoUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
TakenCourseInfoUI::~TakenCourseInfoUI() {
  //cout << "DESTRUCT TakenCourseInfoUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Sets the widgets to the correct selection
void TakenCourseInfoUI::setWidgets(){  
  string text;
  int i=0;

  text = taken->getName();
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();
  while (currNode != 0){ 
    if (currNode->data->getName() == text) {
      courseCombo.set_active(i);
      break;
    }
    i++;
    currNode = currNode->next;
  }

  text = taken->getTerm();
  for (i=0; i<MAX_BUF; i++){
    if(term[i] == text) {
      termCombo.set_active(i);
      break;
    }
  }

  text = taken->getYear();
  for (i=0; i<MAX_BUF; i++){
    if(year[i] == text) {
      yearCombo.set_active(i);
      break;
    }
  }

  text = taken->getFinalGrade();
  for (i=0; i<MAX_BUF; i++){
    if(final[i] == text) {
      finalCombo.set_active(i);
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler of next button
void TakenCourseInfoUI::on_nextButton(const Glib::ustring& data){
  taken->setName(courseCombo.get_active_text());
  taken->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());
  uApp->getTakenCrsQueue()->pushBack(taken);    
  TACourseInfoUI* taCrsInfoWin = new TACourseInfoUI(manager, 1, 0, uApp, 0); 
  taCrsInfoWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of back button
void TakenCourseInfoUI::on_backButton(const Glib::ustring& data){  
  // Clear queue
  if (uApp != 0) { 
    if (!(uApp->getTakenCrsQueue()->empty()));
      uApp->getTakenCrsQueue()->clear();
    manager->cancelApp();
    StuAppFormUI* stuFormWin = new StuAppFormUI(manager, 1, 0);
    stuFormWin->show();
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler of course button
void TakenCourseInfoUI::on_courseButton(const Glib::ustring& data){ 
  taken->setName(courseCombo.get_active_text());
  taken->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());
  uApp->getTakenCrsQueue()->pushBack(taken);

  TakenCourseInfoUI* takenCrsInfoWin = new TakenCourseInfoUI(manager, 1, 0, uApp, 0);
  takenCrsInfoWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of cancel button
void TakenCourseInfoUI::on_cancelButton(const Glib::ustring& data){
  SelectEntryUI* selectEntryWin = new SelectEntryUI(manager, 0, 0, uApp->getAppNum());
  selectEntryWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of save button
void TakenCourseInfoUI::on_saveButton(const Glib::ustring& data){
  taken->setName(courseCombo.get_active_text());
  taken->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());
  if (addCrs)
    uApp->getTakenCrsQueue()->pushBack(taken);

  SelectEntryUI* selectEntryWin = new SelectEntryUI(manager, 0, 0, uApp->getAppNum());
  selectEntryWin->show();
  delete this;
}
