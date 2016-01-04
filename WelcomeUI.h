//////////////////////////////////////////////////////////////////////////
// WELCOME UI
// Prompts the user to select if they are a student or an administrator

#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include "Types.h"
#include <gtkmm.h>

class WelcomeUI : public Gtk::Window {
  public:
    WelcomeUI(Manager*);
    ~WelcomeUI();

    Manager* manager;

  private:
    // Signal handlers
    void on_stuButton(const Glib::ustring& data);
    void on_adminButton(const Glib::ustring& data);

    // Child widgets
    Gtk::Table 	aTable;
    Gtk::Label	aTitle;
    Gtk::Button stuButton, adminButton;
};

#endif
