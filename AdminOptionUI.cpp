//////////////////////////////////////////////////////////////////////////
// ADMINISTRATION OPTION UI
// Prompts user to select and administrator feature

#include "AdminOptionUI.h"
#include "SelectCrsUI.h"
#include "AllPendingUI.h"
#include "AllAssignedUI.h"
#include "StuNumUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
AdminOptionUI::AdminOptionUI(Manager* aManager) 
: aTable(3, 2, false),
  aLabel("Please select an option:"),
  nextButton("Next"),
  backButton("Back")
{
  manager = aManager;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  add(aTable);

  adminCombo.append("View an application");
  adminCombo.append("Assign successful applicant");
  adminCombo.append("View a summary of pending applications");
  adminCombo.append("View a summary of assigned applications");
  adminCombo.append("View and edit a TA evaluation");
  adminCombo.set_active(0);

  aCombo.append("By application number");
  aCombo.append("By applicants student number");
  aCombo.append("By applicants name");

  bCombo.append("View a summary of pending applications for ONE course");
  bCombo.append("View a summary of pending applications for ALL courses");

  cCombo.append("View a summary of assigned applications for ONE course");
  cCombo.append("View a summary of assigned applications for ALL courses");  

  aTable.attach(aLabel, 0, 1, 0, 1,Gtk::FILL,Gtk::FILL,20,40);
  aTable.attach(adminCombo, 1, 2, 0, 1, Gtk::FILL,Gtk::FILL,25,60);
  aTable.attach(aCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(bCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(cCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(empCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(backButton, 0, 1, 2, 3, Gtk::FILL,Gtk::FILL,30,56);
  aTable.attach(nextButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,100,56);

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AdminOptionUI::on_nextButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AdminOptionUI::on_backButton), "Back") );
  adminCombo.signal_changed().connect(
    sigc::mem_fun(*this, &AdminOptionUI::on_combo_change) );

  show_all_children();
  //cout << "CONSTRUCT AdminOptionUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
AdminOptionUI::~AdminOptionUI() {
  //cout << "DESTRUCT AdminOptionUI" << endl;
}


//////////////////////////////////////////////////////////////////////////
// Event handler for the combobox
void AdminOptionUI::on_combo_change(){
  if(adminCombo.get_active_text() == "View an application")
     aCombo.show();
  else aCombo.hide();
  if(adminCombo.get_active_text() == "View a summary of pending applications")
     bCombo.show();
  else bCombo.hide();
  if(adminCombo.get_active_text() == "View a summary of assigned applications")
     cCombo.show();
  else cCombo.hide();
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the next button
void AdminOptionUI::on_nextButton(const Glib::ustring& data){
  if(bCombo.get_active_text() == "View a summary of pending applications for ONE course"){
    SelectCrsUI* selectWin = new SelectCrsUI(manager, 0); 
    selectWin->show();  
  }
  else if(bCombo.get_active_text() == "View a summary of pending applications for ALL courses"){
    AllPendingUI* allPending = new AllPendingUI(manager);
    allPending->show();
  }
  else if (cCombo.get_active_text() == "View a summary of assigned applications for ONE course"){
    SelectCrsUI* selectWin = new SelectCrsUI(manager, 1); 
    selectWin->show();  
  }
  else if (cCombo.get_active_text() == "View a summary of assigned applications for ALL courses"){
    AllAssignedUI* allAssignedApps = new AllAssignedUI(manager);
    allAssignedApps->show();
  }
  else if (adminCombo.get_active_text() == "Assign successful applicant"){
    StuNumUI* stuNumWin = new StuNumUI(manager, 3, 1);
    stuNumWin->show();
  }
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void AdminOptionUI::on_backButton(const Glib::ustring& data){
  delete this;
}
