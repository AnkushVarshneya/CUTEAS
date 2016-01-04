//////////////////////////////////////////////////////////////////////////
// STUDENT OPTION WINDOW
// Prompts user to select if they want to CREATE or EDIT an application

#ifndef STUOPTIONUI_H 
#define STUOPTIONUI_H

#include "Types.h"
#include <gtkmm.h>

class StuOptionUI : public Gtk::Window {
  public:
    StuOptionUI(Manager*);
    ~StuOptionUI();

    Manager* manager;

  private:
    void on_createButton(const Glib::ustring& data);
    void on_editButton  (const Glib::ustring& data);
    void on_backButton  (const Glib::ustring& data);

    Gtk::Table         stuTable;
    Gtk::Label	       stuLabel;
    Gtk::ComboBoxText  m_Combo;
    Gtk::Button        createButton, editButton, backButton;
};

#endif
