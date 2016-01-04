//////////////////////////////////////////////////////////////////////////
// SELECT EDIT WINDOW
// Displays a student's applications and allows student to choose which 
// part of the application to edit

#include "SelectEditUI.h"
#include "Tools.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "SelectAppUI.h"
#include "TakenCourseQueue.h"
#include "TACourseQueue.h"
#include "WorkExpQueue.h"
#include "StuAppFormUI.h"
#include "GradAppFormUI.h"
#include "SelectEntryUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
SelectEditUI::SelectEditUI(Manager* aManager, int type, int app) 
: aTable(11, 6, false),
  title("Please select a section to edit"),
  l1("General Information:", 0, 1, false),
  l2("Taken Courses:", 0, 1, false),
  l3("TA'd Courses:", 0, 1, false),
  l4("Work Experience:", 0, 1, false),
  e1("Edit"),
  e2("Edit"),
  e3("Edit"),
  e4("Edit"),
  cancelButton("Cancel Application"),
  doneButton("Done"), 
  uApp(0),
  gApp(0)
{
  manager = aManager;
  stuType = type;
  appNum  = app;

  set_default_size(500, 700);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  if (stuType == 0) {
    uApp = manager->getUGradApps()->getApp(appNum);
    appInfo.set_text("Application #" + Tools::intToString(appNum) + " for " + uApp->getCourse()->getName());
  }
  else {
    gApp = manager->getGradApps()->getApp(appNum);
    appInfo.set_text("Application #" + Tools::intToString(appNum) + " for " + gApp->getCourse()->getName());
  }

  add(aTable);
  fillTable();
  aTable.attach(title, 0, 6, 0, 1,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(appInfo, 0, 6, 1, 2,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(l1, 0, 6, 2, 3,Gtk::FILL,Gtk::FILL,15,0);
  aTable.attach(s1, 0, 4, 3, 4);
  aTable.attach(e1, 4, 6, 3, 4,Gtk::FILL,Gtk::SHRINK,15,0);
  if (stuType==0) {
    aTable.attach(l2, 0, 6, 4, 5,Gtk::FILL,Gtk::FILL,15,0);
    aTable.attach(s2, 0, 4, 5, 6);
    aTable.attach(e2, 4, 6, 5, 6,Gtk::FILL,Gtk::SHRINK,15,0);
  }
  aTable.attach(l3, 0, 6, 6, 7,Gtk::FILL,Gtk::FILL,15,0);
  aTable.attach(s3, 0, 4, 7, 8);
  aTable.attach(e3, 4, 6, 7, 8,Gtk::FILL,Gtk::SHRINK,15,0);
  aTable.attach(l4, 0, 6, 8, 9,Gtk::FILL,Gtk::FILL,15,0);
  aTable.attach(s4, 0, 4, 9, 10);
  aTable.attach(e4, 4, 6, 9, 10,Gtk::FILL,Gtk::SHRINK,15,0);
  aTable.attach(cancelButton, 0, 2, 10, 11, Gtk::FILL,Gtk::FILL, 20, 20);
  aTable.attach(doneButton, 2, 6, 10, 11, Gtk::FILL, Gtk::FILL, 20, 20);

  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEditUI::on_cancelButton), "Cancel Application") );
  doneButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEditUI::on_doneButton), "Done") );
  e1.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEditUI::on_editInfoButton), "info") );
  e2.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEditUI::on_editEntryButton), "taken") );
  e3.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEditUI::on_editEntryButton), "ta") );
  e4.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEditUI::on_editEntryButton), "work") );
  
  show_all_children();
  //cout << "CONSTRUCT SelectEditUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
SelectEditUI::~SelectEditUI() {
  //cout << "DESTRUCT SelectEditUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the cancel application button
void SelectEditUI::on_cancelButton(const Glib::ustring& data){  
  Gtk::MessageDialog dialog(*this, "Application has been cancelled");
  if (stuType == 0) 
    uApp->operator-();
  else 
    gApp->operator-();
  dialog.run();
  on_doneButton(data);
}

////////////////////////////////////////////////////////////////////////// 
// Event handler for the done button
void SelectEditUI::on_doneButton(const Glib::ustring& data) {
  SelectAppUI* selectAppWin;

  if (stuType == 0)
    selectAppWin = new SelectAppUI(manager, stuType, uApp->getUndergrad()->getStuNum());
  else
    selectAppWin = new SelectAppUI(manager, stuType, gApp->getGrad()->getStuNum());

  selectAppWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handlers for the edit Gen Info button
void SelectEditUI::on_editInfoButton(const Glib::ustring& data) {
  if (stuType == 0) {
    StuAppFormUI* stuFormWin = new StuAppFormUI(manager, 2, uApp);
    stuFormWin->show();  
    delete this;
  }
  else {
    GradAppFormUI* gradFormWin = new GradAppFormUI(manager, 2, gApp);
    gradFormWin->show();  
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handlers for the edit entry buttons
void SelectEditUI::on_editEntryButton(const Glib::ustring& data) {
  SelectEntryUI* selectEntryWin;
  
  if (data =="taken")
    selectEntryWin = new SelectEntryUI(manager, 0, stuType, appNum);
  else if (data == "ta")
    selectEntryWin = new SelectEntryUI(manager, 1, stuType, appNum);
  else
    selectEntryWin = new SelectEntryUI(manager, 2, stuType, appNum);

  selectEntryWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the table to display the application
void SelectEditUI::fillTable() {
  s1.set_border_width(15);
  s1.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 
  s1.add(t1);
  b1 = Gtk::TextBuffer::create();
  if (stuType == 0)
    b1->set_text(uApp->getUndergrad()->print());
  else
    b1->set_text(gApp->getGrad()->print());
  t1.set_buffer(b1);
  t1.set_editable(false);

  if (stuType == 0) {
    s2.set_border_width(15);
    s2.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 
    s2.add(t2);
    b2 = Gtk::TextBuffer::create();
    b2->set_text(uApp->getTakenCrsQueue()->print());
    t2.set_buffer(b2);
    t2.set_editable(false);
  }

  s3.set_border_width(15);
  s3.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 
  s3.add(t3);
  b3 = Gtk::TextBuffer::create();
  if (stuType == 0)
    b3->set_text(uApp->getTACrsQueue()->print());
  else
    b3->set_text(gApp->getTACrsQueue()->print());
  t3.set_buffer(b3);
  t3.set_editable(false);

  s4.set_border_width(15);
  s4.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 
  s4.add(t4);
  b4 = Gtk::TextBuffer::create();
  if (stuType == 0)
    b4->set_text(uApp->getWorkExpQueue()->print());
  else
    b4->set_text(gApp->getWorkExpQueue()->print());
  t4.set_buffer(b4);
  t4.set_editable(false);

}

