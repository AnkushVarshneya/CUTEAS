//////////////////////////////////////////////////////////////////////////
// SELECT APP WINDOW
// Prompts user to select one of their pending applications

#ifndef SELECTAPP_H 
#define SELECTAPP_H

#include "Types.h"
#include <gtkmm.h>

class SelectAppUI : public Gtk::Window {
  public:
    SelectAppUI(Manager*, int, string);
    ~SelectAppUI();

    Manager* manager;

  private:
    void on_backButton(const Glib::ustring& data);
    void on_nextButton(const Glib::ustring& data);
    void fillList();

    Gtk::Table          aTable;
    Gtk::Label	        aLabel;
    Gtk::ListViewText   list;
    Gtk::Button         backButton, nextButton;
    Gtk::ScrolledWindow scrolledWindow;

    // 0 = UGrad; 
    // 1 = Grad;
    int    stuType; 

    string stuNum;
};

#endif
