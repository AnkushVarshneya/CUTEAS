//////////////////////////////////////////////////////////////////////////
// STUDENT NUMBER WINDOW
// Prompts user to enter their student number to edit an application

#ifndef STUNUMUI_H 
#define STUNUMUI_H

#include "Types.h"
#include <gtkmm.h>
#include "UGradApp.h"
#include "GradApp.h"

class StuNumUI : public Gtk::Window {
  public:
    StuNumUI(Manager*, int, int);
    ~StuNumUI();

    Manager* manager;

  private:
    void on_backButton(const Glib::ustring& data);
    void on_nextButton(const Glib::ustring& data);

    Gtk::Table     aTable;
    Gtk::Label	   aLabel;
    Gtk::Entry     entry;
    Gtk::Button    backButton, nextButton;

    // 0 = UGrad
    // 1 = Grad
    // 3 = checkBoth
    int stuType;

    // 0 = Student
    // 1 = Admin
    int userType;

    UGradApp* tempUApp;
    GradApp*  tempGApp;
};

#endif
