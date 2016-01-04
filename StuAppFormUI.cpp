//////////////////////////////////////////////////////////////////////////
// STUDENT APPLICATION FORM WINDOW
// Prompts user to input their general information

#include <locale>  // for isdigit, isalpha, ispunct, char_traits
#include <fstream>
#include <string>

#include "StuAppFormUI.h"
#include "UGradAppQueue.h"
#include "TakenCourseInfoUI.h"
#include "StuOptionUI.h"
#include "Tools.h"
#include "CourseQueue.h"
#include "SelectEditUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
StuAppFormUI::StuAppFormUI(Manager* aManager, int prev, UGradApp* uApp) 
: appTable(11, 3, false),
  label("Please enter your information: "),
  nextButton("Next"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;
  prevWin = prev; 
  if (uApp) // If an application was passed in, assign it to app
    app = uApp;
  else {    // Else make a new application
    manager->makeNewUGradApp();
    app = manager->getCurrUGradApp();
  }
  int i=0, count=0;

  set_default_size(700, 475);
  set_title("cuTAES");
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);
  
  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
  get_vbox()->pack_start(scrolledWindow);
  appTable.set_row_spacings(11);
  appTable.set_col_spacings(3);

  // Add labels
  appTable.attach(label, 0, 4, 0, 1);
  string stuLabels[9] = {"Select a Course to TA for:", "Student Number*: ", "First Name*: ", "Surname*: ", "Email*: ", 
			 "Major*: ", "Current Year Standing*: ", "CPGA*: ", "Major GPA*: " };		      
  for(i = 0; i < 9; i++) {
    if (!(prevWin == 2 && i == 0)) {
      aLabel = Gtk::manage(new Gtk::Label(stuLabels[i]));
      aLabel->set_alignment(0, 0.5);
      appTable.attach(*aLabel, 0, 1, i + 1, i + 2);
    }
  }

  // Email combo box
  emailCombo.append("@cmail.carleton.ca");
  emailCombo.append("@connect.carleton.ca");
  
  // Courses combo box
  // Iterate through course queue and put names into comboBox
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();

  while (currNode != 0){ 
    courseCombo.append(currNode->data->getName());
    currNode = currNode->next;
  }
  courseCombo.set_active(0);

  // Fill in Major combo box from file
  string majors[350];

  ifstream infile("majors.txt", ios::in);
  if (!infile) 
    cout << "Could not open file" << endl;
  
  while (!infile.eof()) {
    getline(infile, majors[count]);
    count++;
  }

  for (i=0; i<(count); i++) 
    majorCombo.append(majors[i]);
  
  // If the user already made application this session
  if (app->getUndergrad()->getStuNum() != "000000000") {
    string text, emailName, emailDomain, aMajor;

    stuNumEntry.set_text(app->getUndergrad()->getStuNum());
    nameEntry.set_text(app->getUndergrad()->getFirstName());
    surnameEntry.set_text(app->getUndergrad()->getSurname());

    text = app->getUndergrad()->getEmail();
    emailName = text.substr(0, text.find("@"));
    emailDomain = text.substr(text.find("@"));

    emailEntry.set_text(emailName);
    if (emailDomain == "@cmail.carleton.ca")
      emailCombo.set_active(0);
    else
      emailCombo.set_active(1);

    aMajor = app->getUndergrad()->getMajor();
    for (i=0; i<count; i++) {
       if (majors[i] == aMajor) {
         majorCombo.set_active(i);
         break;
       }
    }    
    yearEntry.set_text(Tools::floatToString(app->getUndergrad()->getYear()));
    cgpaEntry.set_text(Tools::floatToString(app->getUndergrad()->getCGPA()));
    mgpaEntry.set_text(Tools::floatToString(app->getUndergrad()->getMGPA()));
  }
  else {
    emailCombo.set_active(0);
    majorCombo.set_active(0);
  }

  // Add widgets to table
  if (prevWin != 2)
    appTable.attach(courseCombo, 1, 2, 1, 2);
  if (prevWin != 0 && prevWin != 1)
    stuNumEntry.set_editable(false);
  appTable.attach(stuNumEntry, 1, 3, 2, 3);
  appTable.attach(nameEntry, 1, 3, 3, 4);
  appTable.attach(surnameEntry, 1, 3, 4, 5);
  appTable.attach(emailEntry, 1, 2, 5, 6);
  appTable.attach(emailCombo, 2, 3, 5, 6);
  appTable.attach(majorCombo, 1, 3, 6, 7);
  appTable.attach(yearEntry, 1, 3, 7, 8);
  appTable.attach(cgpaEntry, 1, 3, 8, 9);
  appTable.attach(mgpaEntry, 1, 3, 9, 10);
  if (prevWin == 2) {
    appTable.attach(cancelButton, 1, 2, 10, 11);
    appTable.attach(saveButton, 2, 3, 10, 11);
  }
  else {
    appTable.attach(backButton, 1, 2, 10, 11);
    appTable.attach(nextButton, 2, 3, 10, 11);
  }
  scrolledWindow.add(appTable);

  // Widget action listeners
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuAppFormUI::on_backButton), "Back") );
  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuAppFormUI::on_nextButton), "Next") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuAppFormUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuAppFormUI::on_saveButton), "Save") );
  
  show_all_children();

  //cout << "CONSTRUCT StuAppFormUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
StuAppFormUI::~StuAppFormUI() {
  //cout << "DESTRUCT StuAppFormUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Checks if any of the entry fields are empty
int StuAppFormUI::isEmpty() {
  if ((stuNumEntry.get_text()).find_first_not_of(' ')  == string::npos ||
      (nameEntry.get_text()).find_first_not_of(' ')    == string::npos ||
      (surnameEntry.get_text()).find_first_not_of(' ') == string::npos ||
      (emailEntry.get_text()).find_first_not_of(' ')   == string::npos ||
      (yearEntry.get_text()).find_first_not_of(' ')    == string::npos ||
      (cgpaEntry.get_text()).find_first_not_of(' ')    == string::npos ||
      (mgpaEntry.get_text()).find_first_not_of(' ')    == string::npos)
    return 1;
  else
    return 0;
}

//////////////////////////////////////////////////////////////////////////
// Checks if all entries are full and valid
// @return 0 if empty or not valid
// @return 1 if fill and valid
int StuAppFormUI::validEntries(){
  if (isEmpty() || (!Tools::validStuNum(stuNumEntry.get_text()) || !Tools::validName(nameEntry.get_text()) ||
      !Tools::validName(surnameEntry.get_text()) || !Tools::validEmail(emailEntry.get_text()) || !Tools::validNumber(yearEntry.get_text()) || 
      !Tools::validGPA(cgpaEntry.get_text()) || !Tools::validGPA(mgpaEntry.get_text()))) {
    errorDialog();
    return 0;
  }
  return 1;
}

//////////////////////////////////////////////////////////////////////////
// Display error dialog for incorrect entries
void StuAppFormUI::errorDialog(){
  Gtk::MessageDialog dialog(*this, "ERROR!"); 
  dialog.set_secondary_text(
     "You have left fields blank or entered information incorrectly. \nPlease review your entries."); 
  dialog.run();
}

//////////////////////////////////////////////////////////////////////////
// Event handler for back button
void StuAppFormUI::on_backButton(const Glib::ustring& data) {
  manager->cancelApp();
  StuOptionUI* stuOptWin = new StuOptionUI(manager); 
  stuOptWin->show();  
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for next button
void StuAppFormUI::on_nextButton(const Glib::ustring& data) {
  if (validEntries()) {
    CourseQueue::Node* currNode = manager->getCourseQueue()->front();
    while (currNode != 0) {
      if (currNode->data->getName() == courseCombo.get_active_text()) { 
        app->setCourse(currNode->data);
        break;
      }
      currNode = currNode->next;
    }

    if(prevWin == 0 ||prevWin ==1){
      if (manager->getUGradApps()->isInQueue(stuNumEntry.get_text())){
        Gtk::MessageDialog dialog(*this, "WARNING!", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
        dialog.set_secondary_text(
        "There are applications in our system with the same student number.\n Are you sure you want to overwrite this info?"); 
        int result = dialog.run();
        if(result == -6)
          return;
      }
      if (manager->getGradApps()->isInQueue(stuNumEntry.get_text())){
        Gtk::MessageDialog dialog(*this, "ERROR!"); 
        dialog.set_secondary_text(
        "This student number already exists as a graduate student number.\nPlease enter a different student number"); 
        dialog.run();
        return;
      }
    }
    manager->setUGradInfo( stuNumEntry.get_text(),
                           nameEntry.get_text(),
                           surnameEntry.get_text(),
                           emailEntry.get_text() + emailCombo.get_active_text(),
                           majorCombo.get_active_text(),
                           Tools::stringToInt(yearEntry.get_text()),
                           Tools::stringToFloat(cgpaEntry.get_text()),
                           Tools::stringToFloat(mgpaEntry.get_text()) );
      TakenCourseInfoUI* takenCrsInfoWin = new TakenCourseInfoUI(manager, 0, 0, app, 0);
      takenCrsInfoWin->show();
      hide();
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for cancel button
void StuAppFormUI::on_cancelButton(const Glib::ustring& data) {
  SelectEditUI* selectEditWin = new SelectEditUI(manager, 0, app->getAppNum());
  selectEditWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for save button
void StuAppFormUI::on_saveButton(const Glib::ustring& data) {
  if (validEntries()) {
    manager->overwriteInfo( app,
                            nameEntry.get_text(),
                            surnameEntry.get_text(),
                            emailEntry.get_text() + emailCombo.get_active_text(),
                            majorCombo.get_active_text(),
                            Tools::stringToInt(yearEntry.get_text()),
                            Tools::stringToFloat(cgpaEntry.get_text()),
                            Tools::stringToFloat(mgpaEntry.get_text()) );

    SelectEditUI* selectEditWin = new SelectEditUI(manager, 0, app->getAppNum());
    selectEditWin->show();
    delete this;
  }
}
