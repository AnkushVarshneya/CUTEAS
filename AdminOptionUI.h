//////////////////////////////////////////////////////////////////////////
// ADMINISTRATION OPTION UI
// Prompts user to select and administrator feature

#ifndef ADMINOPTIONUI_H 
#define ADMINOPTIONUI_H

#include "Types.h"
#include <gtkmm.h>

class AdminOptionUI : public Gtk::Window {
  public:
    AdminOptionUI(Manager*);
    ~AdminOptionUI();

    Manager* manager;

  private:
    void on_nextButton(const Glib::ustring& data);
    void on_backButton(const Glib::ustring& data);
    void on_combo_change();

    Gtk::Table         aTable;
    Gtk::Label	       aLabel;
    Gtk::ComboBoxText  adminCombo, aCombo, bCombo, cCombo, empCombo;
    Gtk::Button	       nextButton, backButton;
};

#endif
