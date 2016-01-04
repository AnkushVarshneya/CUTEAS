//////////////////////////////////////////////////////////////////////////
// ACCEPT APPLICATION UI
// Prompts the user to either submit or cancel their application

#ifndef ACCEPTAPPUI_H
#define ACCEPTAPPUI_H

#include "Types.h"
#include <gtkmm.h>

class AcceptAppUI : public Gtk::Window {
  public:
    AcceptAppUI( Manager*);
    ~AcceptAppUI();

    Manager*  manager;

  private:
    void on_submitButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);

    Gtk::Table          aTable;
    Gtk::Label          aLabel;    
    Gtk::Button	        submitButton, cancelButton;
};

#endif
