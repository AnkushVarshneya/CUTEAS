//////////////////////////////////////////////////////////////////////////
// SUBMITTED APPLICATION WINDOW
// Informs the user that their application was submitted and displays the
// application status and number

#ifndef SUBMITAPPUI_H
#define SUBMITAPPUI_H

#include "Types.h"
#include <gtkmm.h>

class SubmitAppUI : public Gtk::Window {
  public:
    SubmitAppUI(Manager*);
    ~SubmitAppUI();
 
    Manager*  manager;

  private:
    void on_closeButton (const Glib::ustring& data);
    void on_createButton(const Glib::ustring& data);
   
    Gtk::Table   subTable;
    Gtk::Label   completeLabel, statusLabel1, statusLabel2, appNumLabel1, appNumLabel2;
    Gtk::Entry   statusEntry, appNumEntry;
    Gtk::Button	 closeButton, createButton;
};

#endif
