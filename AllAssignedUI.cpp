///////////////////////////////////////////////////////////////////////////////////////
// ALL ASSIGNED APPLICATIONS WINDOW
// Shows a list of all assigned applications
//   sorted by applicant's major GPA or research area

#include <fstream>

#include "AllAssignedUI.h"
#include "UGradApp.h"
#include "GradApp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
AllAssignedUI::AllAssignedUI(Manager* aManager) 
: AllReportsUI(aManager),
  aTable(3, 3, false),
  aLabel("List of all assigned applications sorted by Major GPA and Research Area"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;

  set_title("cuTAES- All Assigned Applications");

  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);  

  fillSummary(ASSIGNED);

  scrolledWindow.add(summary);

  aTable.attach(aLabel, 0, 2, 0, 1,Gtk::EXPAND,Gtk::FILL,0,10);
  aTable.attach(backButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(cancelButton, 2, 3, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(saveButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(scrolledWindow, 0, 3, 1, 2);

  add(aTable);

  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AllAssignedUI::on_backButton), "Back") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AllAssignedUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AllAssignedUI::on_saveButton), "Save") );

  show_all_children();

  //cout << "CONSTRUCT AllAssignedUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
AllAssignedUI::~AllAssignedUI() {
  //cout << "DESTRUCT AllAssignedUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the save button
void AllAssignedUI::on_saveButton(const Glib::ustring& data){
  string cn = "./AppSummaries/AllAssignedApps";
  int i = 0;

  // Create an output file
  ofstream outFile(cn.c_str(), ios::out); 
  if (!outFile)
    cout << "Could not open file" << endl;

  // Output application information to permanent storage
  outFile << "*NEW SUMMARY OF ALL ASSIGNED APPLICATIONS*" << endl;
  for ( i =0; i< summary.size(); i++){
    outFile << endl;
    if (summary.get_text(i,0) == "--------")
      continue;
    outFile << summary.get_text(i,0) << endl;
    outFile << summary.get_text(i,1) << endl;
    outFile << summary.get_text(i,2) << endl;
    outFile << summary.get_text(i,3) << endl;
    outFile << summary.get_text(i,4) << endl;
    outFile << summary.get_text(i,5) << endl;
    outFile << summary.get_text(i,6) << endl;
    outFile << summary.get_text(i,7) << endl;
    outFile << summary.get_text(i,8) << endl;
    outFile << summary.get_text(i,9) << endl;
  }
  outFile << endl;
  saveDialog();
}

