//////////////////////////////////////////////////////////////////////////
// STUDENT NUMBER WINDOW
// Prompts user to enter their student number to edit an application

#include "StuNumUI.h"
#include "StuOptionUI.h"
#include "AdminOptionUI.h"
#include "Tools.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "SelectAppUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
StuNumUI::StuNumUI(Manager* aManager, int type, int user) 
: aTable(3, 2, false),
  //aLabel("Please enter your student number"),
  backButton("Back"),
  nextButton("Next")
{
  manager  = aManager;
  stuType  = type; 
  userType = user; 

  set_default_size(500, 75);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  add(aTable);

  if (userType == 0)
    aLabel.set_label("Please enter your student number");
  else aLabel.set_label("Please enter the student's application number");

  aTable.attach(aLabel, 0, 2, 0, 1,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(entry, 0, 2 , 1, 2,Gtk::EXPAND,Gtk::FILL,80,10);
  aTable.attach(backButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,10);
  aTable.attach(nextButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,10);

  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuNumUI::on_backButton), "Back") );
  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuNumUI::on_nextButton), "Next") );
  
  show_all_children();
  //cout << "CONSTRUCT StuNumUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
StuNumUI::~StuNumUI() {
  //cout << "DESTRUCT StuNumUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void StuNumUI::on_backButton(const Glib::ustring& data){  
  if (userType == 0){
    StuOptionUI* stuOptWin = new StuOptionUI(manager);
    stuOptWin->show();
  }
  else {
    AdminOptionUI* adminOptWin = new AdminOptionUI(manager);
    adminOptWin->show();
  }
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the next button
void StuNumUI::on_nextButton(const Glib::ustring& data){
  Gtk::MessageDialog dialog(*this, "ERROR!"); 
  Gtk::MessageDialog dialog2(*this, "Applicant has been assigned.");
  int    typeOfStu = 3, 
         temp = Tools::stringToInt(entry.get_text());
  string stuNum, inUQueue, inGQueue;

  // If the entry is empty or is invalid
  if ((entry.get_text()).find_first_not_of(' ')  == string::npos || Tools::validStuNum==0) {
    dialog.set_secondary_text("Please enter a valid student number."); 
    dialog.run();
    return;
  }

  // If there is no application with that student number
  if (userType == 0){
    if (stuType == 0) {
      if (!manager->getUGradApps()->isInQueue(entry.get_text())) {
        dialog.set_secondary_text("There is no such student number found."); 
        dialog.run();
        return;
      }
    }
    else if (stuType == 1) {
      if (!manager->getGradApps()->isInQueue(entry.get_text())) {
        dialog.set_secondary_text("There is no such student number found."); 
        dialog.run();
        return;
      }
    }

    SelectAppUI* selectAppWin = new SelectAppUI(manager, stuType, entry.get_text());
    selectAppWin->show();
    delete this;
  }
  // Checks the status of the application, if closed/assigned or doesn't exist
  // an error message is given otherwise it assigns the applicant, and closes
  // all other applications with the same student number
  else if (userType == 1){
    inUQueue = manager->getUGradApps()->isAppNumInQueue(temp);
    inGQueue = manager->getGradApps()->isAppNumInQueue(temp);
    if(inUQueue != "0"){
      typeOfStu = 0;
      if (inUQueue == "ASSIGNED" || inUQueue == "CLOSED") {
        dialog.set_secondary_text("Application is already assigned or has been closed");
        dialog.run();
        return;
      }
      else {
        tempUApp = manager->getUGradApps()->getApp(temp);
        tempUApp->operator+();
        manager->getUGradApps()->closeOtherUGrad(inUQueue, temp);
        manager->getGradApps()->closeOtherGrad(inUQueue, temp);
      }
    }
    else if(inGQueue != "0"){
      typeOfStu = 1;
      if (inGQueue == "ASSIGNED" || inGQueue == "CLOSED") {
        dialog.set_secondary_text("Application is already assigned or has been closed");
        dialog.run();
        return;
      }
      else {
        tempGApp = manager->getGradApps()->getApp(temp);
        tempGApp->operator+();
        manager->getGradApps()->closeOtherGrad(inGQueue, temp);
        manager->getUGradApps()->closeOtherUGrad(inGQueue, temp);
      }
    }
    else if(typeOfStu == 3){
      dialog.set_secondary_text("There is no application with that number."); 
      dialog.run();
      return;
    }
    dialog2.run();
  }
}


