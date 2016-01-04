//////////////////////////////////////////////////////////////////////////
// GRADUATE APPLICATION FORM WINDOW
// Prompts user to input their general information

#ifndef GRADAPPFORMUI_H
#define GRADAPPFORMUI_H

#include "Types.h"
#include <gtkmm.h>
#include "GradApp.h"

class GradAppFormUI : public Gtk::Dialog {
  public:
    GradAppFormUI(Manager*, int, GradApp*);
    ~GradAppFormUI();

    Manager*  manager;

  private:
    int  isEmpty();
    int  validEntries();
    void errorDialog();
    void on_nextButton(const Glib::ustring& data);
    void on_backButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);
    void on_saveButton(const Glib::ustring& data);

    Gtk::Table               appTable;
    Gtk::Label               label;
    Gtk::Label* 	     aLabel;
    Gtk::ScrolledWindow      scrolledWindow;
    Gtk::ComboBoxText        emailCombo, courseCombo, researchCombo, superCombo;
    Gtk::Entry               stuNumEntry, nameEntry, surnameEntry, emailEntry;
    Gtk::Button	             nextButton, backButton, cancelButton, saveButton;
    Gtk::RadioButton         m_rb1, m_rb2;
    Gtk::RadioButton::Group  group;

    // 0 = StuOptionUI; 
    // 1 = CourseInfoUI; 
    // 2 = SelectEditUI; 
    // 3 = SubmitAppUI;
    int prevWin; 

    GradApp* app;
};

#endif
