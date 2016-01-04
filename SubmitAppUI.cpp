//////////////////////////////////////////////////////////////////////////
// SUBMITTED APPLICATION WINDOW
// Informs the user that their application was submitted and displays the
// application status and number

#include <sstream>

#include "SubmitAppUI.h"
#include "StuAppFormUI.h"
#include "GradAppFormUI.h"
#include "StuOptionUI.h"
#include "CourseQueue.h"
#include "UGradApp.h"
#include "GradApp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
SubmitAppUI::SubmitAppUI(Manager* aManager) 
: subTable(3, 2, true),
  closeButton("Close"),
  createButton("Create New Application"),
  statusLabel1("Application Status: "),
  appNumLabel1("Application Number: ")
{
  manager = aManager;

  set_default_size(675, 475);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);
  add(subTable);  

  if (manager->getCurrUGradApp() != 0) 
    completeLabel.set_text("You have succesfully submitted your application for " + aManager->getCurrUGradApp()->getCourse()->getName());
  else
    completeLabel.set_text("You have succesfully submitted your application for " + aManager->getCurrGradApp()->getCourse()->getName());

  // Set status and app #
  stringstream out;
  if (manager->getCurrUGradApp() != 0) 
    out << manager->getCurrUGradApp()->getAppNum();
  else
    out << manager->getCurrGradApp()->getAppNum();
  string s = out.str();
  appNumLabel2.set_label(s);

  if (manager->getCurrUGradApp() != 0)
    statusLabel2.set_text(manager->getCurrUGradApp()->getStatusString(manager->getCurrUGradApp()->getStatus()));
  else
    statusLabel2.set_text(manager->getCurrGradApp()->getStatusString(manager->getCurrGradApp()->getStatus()));

  // Align labels to the left
  appNumLabel2.set_alignment(0, 0.5);
  statusLabel2.set_alignment(0, 0.5);

  // Attach all the labels 
  subTable.attach(completeLabel, 0, 2, 0, 1);
  subTable.attach(appNumLabel1, 0, 1, 1, 2);
  subTable.attach(appNumLabel2, 1, 2, 1, 2);
  subTable.attach(statusLabel1, 0, 1, 2, 3);
  subTable.attach(statusLabel2, 1, 2, 2, 3);
  subTable.attach(closeButton, 0, 1, 3, 4,Gtk::FILL,Gtk::FILL,75,50);
  subTable.attach(createButton, 1, 2, 3, 4,Gtk::FILL,Gtk::FILL,75,50);

  closeButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SubmitAppUI::on_closeButton), "Close") );
  createButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SubmitAppUI::on_createButton), "Create New Application") );

  show_all_children();

  //cout << "CONSTRUCT SubmitAppUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
SubmitAppUI::~SubmitAppUI() {
  //cout << "DESTRUCT SubmitAppUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for close button
void SubmitAppUI::on_closeButton(const Glib::ustring& data){
  manager->setCurrAppsNull();
  StuOptionUI* studentWin = new StuOptionUI(manager);
  studentWin->show(); 
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for create button
void SubmitAppUI::on_createButton(const Glib::ustring& data){
  if (manager->getCurrUGradApp() != 0) {
    manager->changeUAppMem();  
    StuAppFormUI* stuFormWin = new StuAppFormUI(manager, 3, manager->getCurrUGradApp());
    stuFormWin->show();  
  } 
  else {
    manager->changeGAppMem();  
    GradAppFormUI* gradFormWin = new GradAppFormUI(manager, 3, manager->getCurrGradApp());
    gradFormWin->show();  
  }
  delete this;
}
