///////////////////////////////////////////////////////////////////////////////////////
// ONE PENDING WINDOW
// Shows a list of pending applications for one course, sorted by applicant's major GPA

#ifndef ONEPENDINGUI_H 
#define ONEPENDINGUI_H

#include "OneReportUI.h"
#include "Types.h"
#include <gtkmm.h>

class OnePendingUI : public OneReportUI {
  public:
    OnePendingUI(Manager*, string);
    ~OnePendingUI();

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
