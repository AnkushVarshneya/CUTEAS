///////////////////////////////////////////////////////////////////////////////////////
// ALL ASSIGNED APPLICATIONS WINDOW
// Shows a list of all assigned applications
//   sorted by applicant's major GPA or research area

#ifndef ALLASSIGNEDUI_H 
#define ALLASSIGNEDUI_H

#include "AllReportsUI.h"
#include "Types.h"
#include <gtkmm.h>

class AllAssignedUI : public AllReportsUI {
  public:
    AllAssignedUI(Manager*);
    ~AllAssignedUI();

    Manager* manager;

  private:
    void on_saveButton(const Glib::ustring& data);

    Gtk::Table          aTable;
    Gtk::Label	        aLabel;
    Gtk::Button	        backButton, cancelButton, saveButton;
    Gtk::ScrolledWindow scrolledWindow;
};

#endif
