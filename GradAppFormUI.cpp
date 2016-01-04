//////////////////////////////////////////////////////////////////////////
// GRADUATE APPLICATION FORM WINDOW
// Prompts user to input their general information

#include <fstream>

#include "GradApp.h"
#include "GradAppFormUI.h"
#include "TACourseInfoUI.h"
#include "StuOptionUI.h"
#include "TACourseQueue.h"
#include "Tools.h"
#include "SelectEditUI.h"
#include "CourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
GradAppFormUI::GradAppFormUI(Manager* aManager, int prev, GradApp* gApp) 
: appTable(11, 3, false),
  label("Please enter your information: "),
  m_rb1("MCS"),
  m_rb2("PhD"),
  nextButton("Next"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;
  prevWin = prev; 
  if (gApp) // If an application was passed in, assign it to app
    app = gApp;
  else {    // Else make a new application
    manager->makeNewGradApp();
    app = manager->getCurrGradApp();
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
  
  group = m_rb1.get_group(); 
  m_rb2.set_group(group);

  //Add labels
  appTable.attach(label, 0, 4, 0, 1);
  string stuLabels[8] = {"Select a Course to TA for:", "Student Number*:", "First Name*:", "Surname*:", "Email*:", 
			 "Main Research Area*:", "Program*:", "Supervisor Name*: " };		      
  for(i = 0; i < 8; i++) {
    if (!(prevWin == 2 && i == 0)) {
      aLabel = Gtk::manage(new Gtk::Label(stuLabels[i]));
      aLabel->set_alignment(0, 0.5);
      appTable.attach(*aLabel, 0, 1, i + 1, i + 2);
    }
  }
  
  // Email combo box
  emailCombo.append("@cmail.carleton.ca");
  emailCombo.append("@connect.carleton.ca");
  emailCombo.set_active(0);

  // Courses combo box
  // Iterate through course queue and put names into comboBox
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();

  while (currNode != 0){ 
    courseCombo.append(currNode->data->getName());
    currNode = currNode->next;
  }
  courseCombo.set_active(0);

  // Fill in Research combo box from file
  string research[350];

  ifstream infile("research.txt", ios::in);
  if (!infile) 
    cout << "Could not open file" << endl;
  while (!infile.eof()) {
    getline(infile, research[count]);
    count++;
  }
  for (i=0; i<(count); i++) 
    researchCombo.append(research[i]);

  // Fill in Supervisor combo box from file
  string faculty[100];
  count = 0;
 
  ifstream infile2("faculty.txt", ios::in);
  if (!infile2) 
    cout << "Could not open file" << endl;
  while (!infile2.eof()) {
    getline(infile2, faculty[count]);
    count++;
  }
  for (i=0; i<(count); i++) 
    superCombo.append(faculty[i]);


  // If the user already made application this session
  if (app->getGrad()->getStuNum() != "000000000") {
    string text, emailName, emailDomain, aResearch, aSuper;

    stuNumEntry.set_text(app->getGrad()->getStuNum());
    nameEntry.set_text(app->getGrad()->getFirstName());
    surnameEntry.set_text(app->getGrad()->getSurname());

    text = app->getGrad()->getEmail();
    emailName = text.substr(0, text.find("@"));
    emailDomain = text.substr(text.find("@"));

    emailEntry.set_text(emailName);
    if (emailDomain == "@cmail.carleton.ca")
      emailCombo.set_active(0);
    else
      emailCombo.set_active(1);

    aResearch = app->getGrad()->getResearch();
    for (i=0; i<count; i++) {
       if (research[i] == aResearch) {
         researchCombo.set_active(i);
         break;
       }
    }  
    
    if (app->getGrad()->getProgram() == "MCS")
      m_rb1.set_active();
    else 
      m_rb2.set_active();

    aSuper = app->getGrad()->getSupervisor();
    for (i=0; i<count; i++) {
       if (faculty[i] == aSuper) {
         superCombo.set_active(i);
         break;
       }
    }
  }
  else {
    researchCombo.set_active(0);
    superCombo.set_active(0);
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
  appTable.attach(researchCombo, 1, 3, 6, 7);
  appTable.attach(superCombo, 1, 3, 8, 9);
  appTable.attach(m_rb1, 1, 2, 7, 8);
  appTable.attach(m_rb2, 2 , 3, 7, 8);
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
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &GradAppFormUI::on_backButton), "Back") );
  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &GradAppFormUI::on_nextButton), "Next") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &GradAppFormUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &GradAppFormUI::on_saveButton), "Save") );
  
  show_all_children();

  //cout << "CONSTRUCT GradAppFormUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
GradAppFormUI::~GradAppFormUI() {
  //cout << "DESTRUCT GradAppFormUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Checks if any of the entry fields are empty
int GradAppFormUI::isEmpty() {
  if ((stuNumEntry.get_text()).find_first_not_of(' ')  == string::npos ||
      (nameEntry.get_text()).find_first_not_of(' ')    == string::npos ||
      (surnameEntry.get_text()).find_first_not_of(' ') == string::npos ||
      (emailEntry.get_text()).find_first_not_of(' ')   == string::npos)
    return 1;
  else
    return 0;
}

//////////////////////////////////////////////////////////////////////////
// Checks if all entries are full and valid
// @return 0 if empty or not valid
// @return 1 if fill and valid
int GradAppFormUI::validEntries(){
  if (isEmpty() || (!Tools::validStuNum(stuNumEntry.get_text()) || !Tools::validName(nameEntry.get_text()) ||
      !Tools::validName(surnameEntry.get_text()) || !Tools::validEmail(emailEntry.get_text()))) {
    errorDialog();
    return 0;
  }
  return 1;
}


//////////////////////////////////////////////////////////////////////////
// Display error dialog
void GradAppFormUI::errorDialog(){
  Gtk::MessageDialog dialog(*this, "ERROR!"); 
  dialog.set_secondary_text(
     "You have left fields blank or entered information incorrectly. \nPlease review your entries."); 
  dialog.run();
}

//////////////////////////////////////////////////////////////////////////
// Event handler for back button
void GradAppFormUI::on_backButton(const Glib::ustring& data) {
  manager->cancelApp();
  StuOptionUI* stuOptWin = new StuOptionUI(manager); 
  stuOptWin->show();  
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for next button
void GradAppFormUI::on_nextButton(const Glib::ustring& data) {
  if (validEntries()) {
    CourseQueue::Node* currNode = manager->getCourseQueue()->front();
    while (currNode != 0) {
      if (currNode->data->getName() == courseCombo.get_active_text()) { 
        app->setCourse(currNode->data);
        break;
      }
      currNode = currNode->next;
    }

    string program;
    if (m_rb1.get_active() == 1)
      program = "MCS";
    else
      program = "PhD";
    
    if(prevWin == 0 ||prevWin ==1){
      if (manager->getGradApps()->isInQueue(stuNumEntry.get_text())){
        Gtk::MessageDialog dialog(*this, "WARNING!", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
        dialog.set_secondary_text(
        "There are applications in our system with the same student number.\n Are you sure you want to overwrite this info?"); 
        int result = dialog.run();
        if(result == -6)
          return;
      }
      if (manager->getUGradApps()->isInQueue(stuNumEntry.get_text())){
        Gtk::MessageDialog dialog(*this, "ERROR!"); 
        dialog.set_secondary_text(
        "This student number already exists as an undergraduate student number.\nPlease enter a different student number"); 
        dialog.run();
        return;
      }
    }
    manager->setGradInfo( stuNumEntry.get_text(),
                          nameEntry.get_text(),
                          surnameEntry.get_text(),
                          emailEntry.get_text() + emailCombo.get_active_text(),
                          researchCombo.get_active_text(),
                          program,
                          superCombo.get_active_text() );
    TACourseInfoUI* taCrsInfoWin = new TACourseInfoUI(manager, 0, 1, app, 0);
    taCrsInfoWin->show();  
    hide();
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for cancel button
void GradAppFormUI::on_cancelButton(const Glib::ustring& data) {
  SelectEditUI* selectEditWin = new SelectEditUI(manager, 1, app->getAppNum());
  selectEditWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for save button
void GradAppFormUI::on_saveButton(const Glib::ustring& data) {
  if (validEntries()) {
    string program;
    if (m_rb1.get_active() == 1)
      program = "MCS";
    else
      program = "PhD";

    manager->overwriteInfo( app,
                            nameEntry.get_text(),
                            surnameEntry.get_text(),
                            emailEntry.get_text() + emailCombo.get_active_text(),
                            researchCombo.get_active_text(),
                            program,
                            superCombo.get_active_text() );

    SelectEditUI* selectEditWin = new SelectEditUI(manager, 1, app->getAppNum());
    selectEditWin->show();
    delete this;
  }
}
