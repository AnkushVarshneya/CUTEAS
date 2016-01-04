//////////////////////////////////////////////////////////////////////////
// SELECT EDIT WINDOW
// Displays a student's applications and allows student to choose which 
// part of the application to edit

#ifndef SELECTEDIT_H 
#define SELECTEDIT_H

#include "Types.h"
#include <gtkmm.h>
#include "UGradApp.h"
#include "GradApp.h"

class SelectEditUI : public Gtk::Window {
  public:
    SelectEditUI(Manager*, int, int);
    ~SelectEditUI();

    Manager* manager;

  private:
    void on_cancelButton(const Glib::ustring& data);
    void on_doneButton(const Glib::ustring& data);
    void on_editInfoButton(const Glib::ustring& data);
    void on_editEntryButton(const Glib::ustring& data);
    void fillTable();

    Gtk::Table          aTable;
    Gtk::Label	        title, appInfo, l1, l2, l3, l4;
    Gtk::Button         cancelButton, doneButton, e1, e2, e3, e4;
    Gtk::TextView       t1, t2, t3, t4;
    Glib::RefPtr<Gtk::TextBuffer> b1, b2, b3, b4;
    Gtk::ScrolledWindow s1, s2, s3, s4;

    // 0 = UGrad 
    // 1 = Grad
    int stuType; 

    int       appNum;
    UGradApp* uApp;
    GradApp*  gApp;
};

#endif
