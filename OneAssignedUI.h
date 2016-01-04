///////////////////////////////////////////////////////////////////////////////////////
// ONE ASSIGNED APPLICATION WINDOW
// Shows a list of assigned applications for one course, sorted by course

#ifndef ONEASSIGNEDUI_H 
#define ONEASSIGNEDUI_H

#include "OneReportUI.h"
#include "Types.h"
#include <gtkmm.h>

class OneAssignedUI : public OneReportUI {
  public:
    OneAssignedUI(Manager*, string);
    ~OneAssignedUI();

    Manager* manager;

  private:
    void on_backButton(const Glib::ustring& data);
    void on_saveButton(const Glib::ustring& data);

    Gtk::Table          aTable;
    Gtk::Label	        aLabel;
    Gtk::Button	        backButton, cancelButton, saveButton;
    Gtk::ScrolledWindow scrolledWindow;
};

#endif
