//////////////////////////////////////////////////////////////////////////
// SELECT ENTRY WINDOW
// Prompts user to select one of their applications entries to edit or remove
// Also allows user to add a new entry

#include "SelectEntryUI.h"
#include "SelectEditUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "TakenCourseQueue.h"
#include "TACourseQueue.h"
#include "WorkExpQueue.h"
#include "TakenCourseInfoUI.h"
#include "TACourseInfoUI.h"
#include "WorkExpUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
SelectEntryUI::SelectEntryUI(Manager* aManager, int entity, int type, int app)
: aTable(3, 4, false),
  aLabel("Please select an entry you would like to edit, or click \"Add\" to add a new entry"),
  removeButton("Remove"),
  addButton("Add"),
  editButton("Edit"),
  doneButton("Done"),
  list(4, false, Gtk::SELECTION_SINGLE), 
  uApp(0),
  gApp(0)
{
  manager    = aManager;
  entityType = entity; 
  stuType    = type; 
  appNum     = app;

  set_default_size(500, 250);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 

  switch (entityType) {
    case 0: // Taken Course
      list.set_column_title(0, "Course");
      list.set_column_title(1, "Term");
      list.set_column_title(2, "Year");
      list.set_column_title(3, "Final Grade");
      break;
    case 1: // TA'd Course
      list.set_column_title(0, "Course");
      list.set_column_title(1, "Term");
      list.set_column_title(2, "Year");
      list.set_column_title(3, "Supervisor");
      break;
    case 2: // Work Exp
      list.set_column_title(0, "Responsibility");
      list.set_column_title(1, "Duration");
      list.set_column_title(2, "Start Date");
      list.set_column_title(3, "End Date");
      break;
    default: break;
  }

  if (stuType == 0)
    uApp = manager->getUGradApps()->getApp(appNum);
  else
    gApp = manager->getGradApps()->getApp(appNum);

  fillList();
  scrolledWindow.add(list);
  add(aTable);

  aTable.attach(aLabel, 0, 4, 0, 1,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(scrolledWindow, 0, 4, 1, 2);
  aTable.attach(removeButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(addButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(editButton, 2, 3, 2, 3,Gtk::FILL,Gtk::FILL,0,10);
  aTable.attach(doneButton, 3, 4, 2, 3,Gtk::FILL,Gtk::FILL,0,10);

  removeButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEntryUI::on_removeButton), "Remove") );
  addButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEntryUI::on_addButton), "Add") );
  editButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEntryUI::on_editButton), "Edit") );
  doneButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &SelectEntryUI::on_doneButton), "Done") );
  
  show_all_children();
  //cout << "CONSTRUCT SelectEntryUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
SelectEntryUI::~SelectEntryUI() {
  //cout << "DESTRUCT SelectEntryUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the remove button
void SelectEntryUI::on_removeButton(const Glib::ustring& data){  
  // Do not do anything if there are no entries
  if (list.get_text(list.get_selected()[0],0) == "There are no entries")
    return;

  TakenCourseQueue::Node* takenNode;
  TACourseQueue::Node*    taNode;
  WorkExpQueue::Node*     workNode;

  /* Note: Pass in all data members because unable to get index of row 
   *       selected from ListViewText and to ensure that the correct item 
   *       is removed in case there are two entries with the same name.
   */

  switch (entityType) {
    case 0: // Taken Course
      if (stuType == 0)
        uApp->getTakenCrsQueue()->remove(list.get_text(list.get_selected()[0],0),
                                         list.get_text(list.get_selected()[0],1),
                                         list.get_text(list.get_selected()[0],2),
                                         list.get_text(list.get_selected()[0],3) );
      break;
    case 1: // TA'd Course
      if (stuType == 0)
        uApp->getTACrsQueue()->remove(list.get_text(list.get_selected()[0],0),
                                      list.get_text(list.get_selected()[0],1),
                                      list.get_text(list.get_selected()[0],2),
                                      list.get_text(list.get_selected()[0],3) );
      else
        gApp->getTACrsQueue()->remove(list.get_text(list.get_selected()[0],0),
                                      list.get_text(list.get_selected()[0],1),
                                      list.get_text(list.get_selected()[0],2),
                                      list.get_text(list.get_selected()[0],3) );
      break;
    case 2: // Work Exp
      if (stuType == 0)
        uApp->getWorkExpQueue()->remove(list.get_text(list.get_selected()[0],0),
                                        list.get_text(list.get_selected()[0],1),
                                        list.get_text(list.get_selected()[0],2),
                                        list.get_text(list.get_selected()[0],3) );
      else
        gApp->getWorkExpQueue()->remove(list.get_text(list.get_selected()[0],0),
                                        list.get_text(list.get_selected()[0],1),
                                        list.get_text(list.get_selected()[0],2),
                                        list.get_text(list.get_selected()[0],3) );
      break;
    default:
      break;
  }

  SelectEntryUI* selectEntryWin = new SelectEntryUI(manager, entityType, stuType, appNum);
  selectEntryWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the add button
void SelectEntryUI::on_addButton(const Glib::ustring& data){
  TakenCourseInfoUI* takenCrsInfoWin; 
  TACourseInfoUI*    taCrsInfoWin; 
  WorkExpUI*         workExpWin;

  switch (entityType) {
    case 0: // Taken Course
      if (stuType == 0) {
        takenCrsInfoWin = new TakenCourseInfoUI(manager, 3, 0, uApp, 0);
        takenCrsInfoWin->show();
        delete this;
      }
      break;
    case 1: // TA'd Course
      if (stuType == 0) {
        taCrsInfoWin = new TACourseInfoUI(manager, 3, 0, uApp, 0);
        taCrsInfoWin->show();
        delete this;
      }
      else {
        taCrsInfoWin = new TACourseInfoUI(manager, 3, 1, gApp, 0);
        taCrsInfoWin->show();
        delete this;
      }
      break;
    case 2: // Work Exp
      if (stuType == 0) {
        workExpWin = new WorkExpUI(manager, 1, 0, uApp, 0);
        workExpWin->show();
        delete this;
      }
      else {
        workExpWin = new WorkExpUI(manager, 1, 1, gApp, 0);
        workExpWin->show();
        delete this;
      }
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the edit button
void SelectEntryUI::on_editButton(const Glib::ustring& data){
  // Do not do anything if there are no entries
  if (list.get_text(list.get_selected()[0],0) == "There are no entries")
    return;

  TakenCourseInfoUI* takenCrsInfoWin; 
  TACourseInfoUI*    taCrsInfoWin; 
  WorkExpUI*         workExpWin;

  /* Note: Pass in all data members because unable to get index of row 
   *       selected from ListViewText and to ensure that the correct item 
   *       is edited in case there are two entries with the same name.
   */

  switch (entityType) {
    case 0: // Taken Course
      if (stuType == 0) {
        TakenCourse* taken = uApp->getTakenCrsQueue()->getCourse( list.get_text(list.get_selected()[0],0),
                                                                  list.get_text(list.get_selected()[0],1),
                                                                  list.get_text(list.get_selected()[0],2),
                                                                  list.get_text(list.get_selected()[0],3) );
        takenCrsInfoWin = new TakenCourseInfoUI(manager, 3, 0, uApp, taken);
        takenCrsInfoWin->show();
        delete this;
      }
      break;
    case 1: // TA'd Course
      if (stuType == 0) {
        TACourse* ta = uApp->getTACrsQueue()->getCourse( list.get_text(list.get_selected()[0],0),
                                                         list.get_text(list.get_selected()[0],1),
                                                         list.get_text(list.get_selected()[0],2),
                                                         list.get_text(list.get_selected()[0],3) );
        taCrsInfoWin = new TACourseInfoUI(manager, 3, 0, uApp, ta);
        taCrsInfoWin->show();
        delete this;
      }
      else {
        TACourse* ta = gApp->getTACrsQueue()->getCourse( list.get_text(list.get_selected()[0],0),
                                                         list.get_text(list.get_selected()[0],1),
                                                         list.get_text(list.get_selected()[0],2),
                                                         list.get_text(list.get_selected()[0],3) );
        taCrsInfoWin = new TACourseInfoUI(manager, 3, 1, gApp, ta);
        taCrsInfoWin->show();
        delete this;
      }
      break;
    case 2: // Work Exp
      if (stuType == 0) {
        WorkExp* work = uApp->getWorkExpQueue()->getWork( list.get_text(list.get_selected()[0],0),
                                                          list.get_text(list.get_selected()[0],1),
                                                          list.get_text(list.get_selected()[0],2),
                                                          list.get_text(list.get_selected()[0],3) );
        workExpWin = new WorkExpUI(manager, 1, 0, uApp, work);
        workExpWin->show();
        delete this;
      }
      else {
        WorkExp* work = gApp->getWorkExpQueue()->getWork( list.get_text(list.get_selected()[0],0),
                                                          list.get_text(list.get_selected()[0],1),
                                                          list.get_text(list.get_selected()[0],2),
                                                          list.get_text(list.get_selected()[0],3) );
        workExpWin = new WorkExpUI(manager, 1, 0, gApp, work);
        workExpWin->show();
        delete this;
      }
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the done button
void SelectEntryUI::on_doneButton(const Glib::ustring& data){
  SelectEditUI* selectEditWin = new SelectEditUI(manager, stuType, appNum);
  selectEditWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the ListViewText widget with appropriate information
void SelectEntryUI::fillList() {
  int i = 0;
  TakenCourseQueue::Node* takenNode;
  TACourseQueue::Node*    taNode;
  WorkExpQueue::Node*     workNode;

  switch (entityType) {
    case 0: // Taken Course
      if (stuType == 0)
        takenNode = uApp->getTakenCrsQueue()->front();
      if (takenNode == 0) {
        list.append("");
        list.set_text(i, 0, "There are no entries");
        i++;
        return;
      }  
      while (takenNode != 0) {
        list.append("");
        list.set_text(i, 0, takenNode->data->getName());
        list.set_text(i, 1, takenNode->data->getTerm());
        list.set_text(i, 2, takenNode->data->getYear());
        list.set_text(i, 3, takenNode->data->getFinalGrade());
        i++;
        takenNode = takenNode->next;
      }
      break;
    case 1: // TA'd Course
      if (stuType == 0)
        taNode = uApp->getTACrsQueue()->front();
      else
        taNode = gApp->getTACrsQueue()->front();
      if (taNode == 0) {
        list.append("");
        list.set_text(i, 0, "There are no entries");
        i++;
        return;
      }  
      while (taNode != 0) {
        list.append("");
        list.set_text(i, 0, taNode->data->getName());
        list.set_text(i, 1, taNode->data->getTerm());
        list.set_text(i, 2, taNode->data->getYear());
        list.set_text(i, 3, taNode->data->getSupervisor());
        i++;
        taNode = taNode->next;
      }
      break;
    case 2: // Work Exp
      if (stuType == 0)
        workNode = uApp->getWorkExpQueue()->front();
      else
        workNode = gApp->getWorkExpQueue()->front();
      if (workNode == 0) {
        list.append("");
        list.set_text(i, 0, "There are no entries");
        i++;
        return;
      }  
      while (workNode != 0) {
        list.append("");
        list.set_text(i, 0, workNode->data->getResp());
        list.set_text(i, 1, workNode->data->getDuration());
        list.set_text(i, 2, workNode->data->getStart());
        list.set_text(i, 3, workNode->data->getEnd());
        i++;
        workNode = workNode->next;
      }
      break;
    default:
      break;
  }
}
