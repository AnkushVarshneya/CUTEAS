//////////////////////////////////////////////////////////////////////////
// SELECT APP WINDOW
// Prompts user to select one of their pending applications

#include "SelectAppUI.h"
#include "StuNumUI.h"
#include "UGradInfoQueue.h"
#include "GradInfoQueue.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "Tools.h"
#include "SelectEditUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
SelectAppUI::SelectAppUI(Manager* aManager, int type, string aStuNum) 
: aTable(3, 2, false),
  aLabel("Please select an application you would like to edit"),
  backButton("Back"),
  nextButton("Next"),
  list(2, false, Gtk::SELECTION_SINGLE)
{
  manager = aManager;
  stuType = type;
  stuNum  = aStuNum;

  set_default_size(500, 250);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 

  list.set_column_title(0, "Application #");
  list.set_column_title(1, "Course");

  fillList();

  scrolledWindow.add(list);

  add(aTable);

  aTable.attach(aLabel, 0, 2, 0, 1,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(scrolledWindow, 0, 2, 1, 2);
  aTable.attach(backButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,10);
  aTable.attach(nextButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,10);

  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectAppUI::on_backButton), "Back") );
  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectAppUI::on_nextButton), "Next") );
  
  show_all_children();
  //cout << "CONSTRUCT SelectAppUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
SelectAppUI::~SelectAppUI() {
  //cout << "DESTRUCT SelectAppUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void SelectAppUI::on_backButton(const Glib::ustring& data){  
  StuNumUI* stuNumWin;
  if (stuType == 0)
    stuNumWin = new StuNumUI(manager, 0, 0);
  else
    stuNumWin = new StuNumUI(manager, 1, 0);
  stuNumWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the next button
void SelectAppUI::on_nextButton(const Glib::ustring& data){
  // Do not do anything if there are no pending applications
  if (list.get_text(list.get_selected()[0],0) == "There are no pending applications")
    return;

  SelectEditUI* selectEditWin
    = new SelectEditUI(manager, stuType, Tools::stringToInt(list.get_text(list.get_selected()[0],0)));
  selectEditWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the ListViewText widget with appropriate information
void SelectAppUI::fillList() {
  int i = 0;

  // If it is an Undergraduate
  if (stuType == 0) {
    UGradAppQueue::Node* uAppNode = manager->getUGradInfo()->isInQueue(stuNum)->getApps()->front();

    // If UGradAppQueue is empty
    if (uAppNode == 0) {
      list.append("");
      list.set_text(i, 0, "There are no pending applications");
      i++;
      return;
    }  

    // Add only pending applications
    while (uAppNode != 0) {
      if (uAppNode->data->getStatus() == PENDING) {
        list.append("");
        list.set_text(i, 0, Tools::intToString(uAppNode->data->getAppNum()));
        list.set_text(i, 1, uAppNode->data->getCourse()->getName());
        i++;
      }
      uAppNode = uAppNode->next;
    }

    // If there are no PENDING Applications
    if (i == 0) {
      list.append("");
      list.set_text(i, 0, "There are no pending applications");
    }
  }
  // If it is a Graduate
  else if (stuType == 1) {
    GradAppQueue::Node* gAppNode = manager->getGradInfo()->isInQueue(stuNum)->getApps()->front();

    // If GradAppQueue is empty
    if (gAppNode == 0) {
      list.append("");
      list.set_text(i, 0, "There are no pending applications");
      i++;
      return;
    }  

    // Add only pending applications
    while (gAppNode != 0) {
      if (gAppNode->data->getStatus() == PENDING) {
        list.append("");
        list.set_text(i, 0, Tools::intToString(gAppNode->data->getAppNum()));
        list.set_text(i, 1, gAppNode->data->getCourse()->getName());
        i++;
      }
      gAppNode = gAppNode->next;
    }

    // If there are no PENDING Applications
    if (i == 0) {
      list.append("");
      list.set_text(i, 0, "There are no pending applications");
    }
  }
}
