//////////////////////////////////////////////////////////////////////////
// CREATE WORK EXPERIENCE UI
// Prompts user to give more information about related work experience 

#include <fstream>

#include "WorkExpUI.h"
#include "AcceptAppUI.h"
#include "TACourseInfoUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "WorkExpQueue.h"
#include "TACourseQueue.h"
#include "SelectEntryUI.h"


//////////////////////////////////////////////////////////////////////////
// Constructor
WorkExpUI::WorkExpUI(Manager* aManager, int prev, int type, UGradApp* app, WorkExp* w) 
: createTable(7, 4, false),
  aLabel("Please fill in the information about your work experience"),
  respLabel("Responsibilities:"), 
  durationLabel("Duration (# Months): "), 
  startLabel("Start (dd/mm/year): "),
  endLabel("End (dd/mm/year): "),
  nextButton("Next"),
  backButton("Back"),
  skipButton("Skip"),
  otherButton("Other Work"),
  cancelButton("Cancel"),
  saveButton("Save"),
  uApp(app),
  gApp(0)
{
  manager = aManager;
  prevWin = prev;
  stuType = type;
  if (w) { // If a WorkExp was passed in, assign it to work
    work = w;
    addWork = FALSE;
  }
  else {   // Else make a new WorkExp
    work = new WorkExp(manager);
    addWork = TRUE;
  }
  initialize();
}

//////////////////////////////////////////////////////////////////////////
// Constructor
WorkExpUI::WorkExpUI(Manager* aManager, int prev, int type, GradApp* app, WorkExp* w) 
: createTable(7, 4, false),
  aLabel("Please fill in the information about your work experience"),
  respLabel("Responsibilities:"), 
  durationLabel("Duration (# Months): "), 
  startLabel("Start (dd/mm/year): "),
  endLabel("End (dd/mm/year): "),
  nextButton("Next"),
  backButton("Back"),
  skipButton("Skip"),
  otherButton("Other Work"),
  cancelButton("Cancel"),
  saveButton("Save"),
  uApp(0),
  gApp(app)
{
  manager = aManager;
  prevWin = prev;
  stuType = type;
  if (w) { // If a WorkExp was passed in, assign it to work
    work = w;
    addWork = FALSE;
  }
  else {   // Else make a new WorkExp
    work = new WorkExp(manager);
    addWork = TRUE;
  }
  initialize();
}

//////////////////////////////////////////////////////////////////////////
// Destructor
WorkExpUI::~WorkExpUI() {
  //cout << "DESTRUCT WorkExpUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Initialize
//   Extension of the constructor
void WorkExpUI::initialize() {
  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);
  add(createTable);


  //Read from file using getline function
  string date[MAX_BUF];
  int    count = 0;

  ifstream infile("date.txt", ios::in);

  if (!infile) {
    cout << "Could not open file" << endl;
  }
  while (!infile.eof()) {
    getline(infile, date[count]);
    count++;
  }

  //Fill the combo
  int i, j;
  for (i=0, j=0; i<(count-1); i++, j++){
    if(date[i] != "~"){
      day1Combo.append(date[i]);
      day2Combo.append(date[i]);
      day[j] = date[i];
    }
    else break;
  }
  for(i=i+1, j=0; i<(count-1); i++, j++){
    if(date[i] != "~"){
      month1Combo.append(date[i]);
      month2Combo.append(date[i]);
      month[j] = date[i];
    }
    else break;
  }
  for(i=i+1, j=0; i<(count-1); i++, j++){
    if(date[i] != "~") {
      monthCombo.append(date[i]);
      duration[j] = date[i];
    }
    else break;
  }
  for(i=i+1, j=0; i<(count-1); i++, j++){
    year1Combo.append(date[i]);
    year2Combo.append(date[i]);
    year[j] = date[i];
  }

  // Set widgets according to the add boolean
  if (addWork) {
    day1Combo.set_active(0);
    day2Combo.set_active(0);
    monthCombo.set_active(0);
    month1Combo.set_active(0); 
    month2Combo.set_active(0);
    year1Combo.set_active(0); 
    year2Combo.set_active(0);
  }
  else
    setWidgets();

  createTable.attach(aLabel, 0, 4, 0, 1, Gtk::FILL,Gtk::FILL,20, 30);
  createTable.attach(respLabel, 0, 1, 1, 2);
  createTable.attach(respEntry, 1, 4, 1, 3);

  createTable.attach(durationLabel, 0, 1, 3, 4);
  createTable.attach(monthCombo, 1, 2, 3, 4, Gtk::FILL,Gtk::FILL,20, 20);

  createTable.attach(startLabel, 0, 1, 4, 5);
  createTable.attach(day1Combo, 1, 2, 4, 5, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(month1Combo, 2, 3, 4, 5, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(year1Combo, 3, 4 ,4, 5, Gtk::FILL,Gtk::FILL,20, 20);

  createTable.attach(endLabel, 0, 1, 5, 6);
  createTable.attach(day2Combo, 1, 2, 5, 6, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(month2Combo, 2, 3, 5, 6, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(year2Combo, 3, 4 ,5, 6, Gtk::FILL,Gtk::FILL,20, 20);

  if (prevWin != 1) { // If previous window was NOT from SelectEntryUI
    createTable.attach(backButton, 0, 1, 6, 7, Gtk::FILL,Gtk::FILL,7, 50);
    createTable.attach(skipButton, 1, 2, 6, 7, Gtk::FILL,Gtk::FILL,5, 50);
    createTable.attach(otherButton, 2, 3, 6, 7, Gtk::FILL,Gtk::FILL,5, 50);
    createTable.attach(nextButton, 3, 4, 6, 7,Gtk::FILL,Gtk::FILL,5, 50);
  }
  else {
    createTable.attach(cancelButton, 0, 2, 6, 7, Gtk::FILL,Gtk::FILL,5, 50);
    createTable.attach(saveButton, 2, 4, 6, 7,Gtk::FILL,Gtk::FILL,5, 50);
  }

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_nextOrOtherButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_backButton), "Back") );
  skipButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_skipButton), "Skip") );
  otherButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_nextOrOtherButton), "Other Work") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_saveButton), "Save") );


  show_all_children();
  //cout << "CONSTRUCT WorkExpUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Sets the widgets to the correct selection
void WorkExpUI::setWidgets(){  
  string text, d, m, y;
  int i=0;

  // Repsonsibility Widget
  respEntry.set_text(work->getResp());

  // Duration Widget
  text = work->getDuration();
  for (i=0; i<MAX_BUF; i++){
    if(duration[i] == text) {
      monthCombo.set_active(i);
      break;
    }
  }

  // Start date Widgets
  text = work->getStart();
  d = text.substr(0, 2);
  m = text.substr(3, 2);
  y = text.substr(6, string::npos);
  for (i=0; i<MAX_BUF; i++){
    if(day[i] == d)
      day1Combo.set_active(i);
    if(month[i] == m)
      month1Combo.set_active(i);
    if(year[i] == y)
      year1Combo.set_active(i);
  }

  // End date Widgets
  text = work->getEnd();
  d = text.substr(0, 2);
  m = text.substr(3, 2);
  y = text.substr(6, string::npos);
  for (i=0; i<MAX_BUF; i++){
    if(day[i] == d)
      day2Combo.set_active(i);
    if(month[i] == m)
      month2Combo.set_active(i);
    if(year[i] == y)
      year2Combo.set_active(i);
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler of next or other button
void WorkExpUI::on_nextOrOtherButton(const Glib::ustring& data){
  // If the Responsibility entry is empty
  if ((respEntry.get_text()).find_first_not_of(' ')  == string::npos) {
    Gtk::MessageDialog dialog(*this, "ERROR!"); 
    dialog.set_secondary_text(
       "Please enter a responsibility."); 
    dialog.run();
    return;
  }
  
  // If the Responsibility entry is NOT empty
  else {
    work->setResp(respEntry.get_text());
    work->setDataMembers(
      monthCombo.get_active_text(),
      day1Combo.get_active_text() + "/" + month1Combo.get_active_text() + "/" + year1Combo.get_active_text(),
      day2Combo.get_active_text() + "/" + month2Combo.get_active_text() + "/" + year2Combo.get_active_text() );

    if (uApp != 0)
      uApp->getWorkExpQueue()->pushBack(work);
    else
      gApp->getWorkExpQueue()->pushBack(work);

    WorkExpUI* workWin; 
    if (data == "Next") {
      AcceptAppUI* acceptWin = new AcceptAppUI(manager);
      acceptWin->show();
    }
    else if (data == "Other Work") {
      if (uApp != 0)
        workWin = new WorkExpUI(manager, 2, 0, uApp, 0); 
      else
        workWin = new WorkExpUI(manager, 2, 1, gApp, 0); 
      workWin->show();
    }
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for skip button
void WorkExpUI::on_skipButton(const Glib::ustring& data){ 
  AcceptAppUI* acceptWin = new AcceptAppUI(manager);
  acceptWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of back button
void WorkExpUI::on_backButton(const Glib::ustring& data){
  TACourseInfoUI* taCrsInfoWin; 
  if (uApp != 0) {
    if (!(uApp->getTACrsQueue()->empty()));
      uApp->getTACrsQueue()->clear();
    taCrsInfoWin = new TACourseInfoUI(manager, 4, 0, uApp, 0); 
  }
  else {
    if (!(gApp->getTACrsQueue()->empty()));
      gApp->getTACrsQueue()->clear();
    taCrsInfoWin = new TACourseInfoUI(manager, 4, 1, gApp, 0); 
  }
  taCrsInfoWin->show();  
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of cancel button
void WorkExpUI::on_cancelButton(const Glib::ustring& data){
  SelectEntryUI* selectEntryWin;

  if (uApp != 0)
    selectEntryWin = new SelectEntryUI(manager, 2, 0, uApp->getAppNum());
  else 
    selectEntryWin = new SelectEntryUI(manager, 2, 1, gApp->getAppNum());
  selectEntryWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of save button
void WorkExpUI::on_saveButton(const Glib::ustring& data){
  // If the Responsibility entry is empty
  if ((respEntry.get_text()).find_first_not_of(' ')  == string::npos) {
    Gtk::MessageDialog dialog(*this, "ERROR!"); 
    dialog.set_secondary_text(
       "Please enter a responsibility."); 
    dialog.run();
    return;
  }

  SelectEntryUI* selectEntryWin; 

  work->setResp(respEntry.get_text());
  work->setDataMembers(
      monthCombo.get_active_text(),
      day1Combo.get_active_text() + "/" + month1Combo.get_active_text() + "/" + year1Combo.get_active_text(),
      day2Combo.get_active_text() + "/" + month2Combo.get_active_text() + "/" + year2Combo.get_active_text() );

  if (uApp != 0) {
    if (addWork)
      uApp->getWorkExpQueue()->pushBack(work);
    selectEntryWin = new SelectEntryUI(manager, 2, 0, uApp->getAppNum());
  }
  else {
    if (addWork)
      gApp->getWorkExpQueue()->pushBack(work);
    selectEntryWin = new SelectEntryUI(manager, 2, 1, gApp->getAppNum());
  } 

  selectEntryWin->show();
  delete this;
}
