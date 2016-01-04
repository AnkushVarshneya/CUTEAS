///////////////////////////////////////////////////////////////////////////////////////
// ALL PENDING WINDOW
// Shows a list of pending applications for all courses
//   sorted by applicant's major GPA or research area

#ifndef ALLPENDINGUI_H 
#define ALLPENDINGUI_H

#include "AllReportsUI.h"
#include "Types.h"
#include <gtkmm.h>

class AllPendingUI : public AllReportsUI {
  public:
    AllPendingUI(Manager*);
    ~AllPendingUI();

    Manager* manager;

  private:
    void on_saveButton(const Glib::ustring& data);

    Gtk::Table          aTable;
    Gtk::Label	        aLabel;
    Gtk::Button	        backButton, cancelButton, saveButton;
    Gtk::ScrolledWindow scrolledWindow;
};

#endif
