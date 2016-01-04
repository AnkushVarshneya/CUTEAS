//////////////////////////////////////////////////////////////////////////
// SELECT COURSE WINDOW
// Prompts user to select a course 

#include <fstream>

#include "SelectCrsUI.h"
#include "AdminOptionUI.h"
#include "OnePendingUI.h"
#include "OneAssignedUI.h"
#include "CourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
SelectCrsUI::SelectCrsUI(Manager* aManager, int i) 
: createTable(2, 2, false),
  createLabel("Select a course to apply for:"),
  nextButton("Continue"),
  backButton("Back")
{
  whichWindow = i;
  manager = aManager;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  add(createTable);
    
  // Iterate through course queue and put names into comboBox
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();

  while (currNode != 0){ 
    m_Combo.append(currNode->data->getName());
    currNode = currNode->next;
  }

  m_Combo.set_active(0);

  createTable.attach(createLabel, 0, 1, 0, 1,Gtk::EXPAND,Gtk::EXPAND,0,100);
  createTable.attach(m_Combo, 1, 2, 0, 1,Gtk::EXPAND,Gtk::EXPAND,0,45);
  createTable.attach(backButton, 0, 1, 1, 2,Gtk::FILL,Gtk::FILL,20,50);
  createTable.attach(nextButton, 1, 2, 1, 2,Gtk::FILL,Gtk::FILL,35,50);

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectCrsUI::on_nextButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectCrsUI::on_backButton), "Back") );

  show_all_children();

  //cout << "CONSTRUCT SelectCrsUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
SelectCrsUI::~SelectCrsUI() {
  //cout << "DESTRUCT SelectCrsUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of next button
void SelectCrsUI::on_nextButton(const Glib::ustring& data){
  if (whichWindow == 0){
    OnePendingUI* onePendWin = new OnePendingUI(manager, m_Combo.get_active_text());
    onePendWin->show();  
  }
  else {
    OneAssignedUI* oneAssignedWin = new OneAssignedUI(manager, m_Combo.get_active_text());
    oneAssignedWin->show(); 
  }
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of back button
void SelectCrsUI::on_backButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();  
  delete this;
}
