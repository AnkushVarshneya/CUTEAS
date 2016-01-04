//////////////////////////////////////////////////////////////////////////
// SELECT ENTRY WINDOW
// Prompts user to select one of their applications entries to edit or remove
// Also allows user to add a new entry

#ifndef SELECTENTRY_H 
#define SELECTENTRY_H

#include "Types.h"
#include <gtkmm.h>

class SelectEntryUI : public Gtk::Window {
  public:
    SelectEntryUI(Manager*, int, int, int);
    ~SelectEntryUI();

    Manager* manager;

  private:
    void on_removeButton(const Glib::ustring& data);
    void on_addButton   (const Glib::ustring& data);
    void on_editButton  (const Glib::ustring& data);
    void on_doneButton  (const Glib::ustring& data);
    void fillList();

    Gtk::Table          aTable;
    Gtk::Label	        aLabel;
    Gtk::ListViewText   list;
    Gtk::Button         removeButton, addButton, editButton, doneButton;
    Gtk::ScrolledWindow scrolledWindow;

    // 0 = Taken Course
    // 1 = TA'd Course
    // 2 = Work Exp
    int entityType; 

    // 0 = UGrad
    // 1 = Grad
    int stuType;    

    int       appNum;
    UGradApp* uApp;
    GradApp*  gApp;

};

#endif
