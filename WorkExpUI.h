//////////////////////////////////////////////////////////////////////////
// CREATE WORK EXPERIENCE UI
// Prompts user to give more information about related work experience

#ifndef WORKEXPUI_H
#define WORKEXPUI_H

#include <gtkmm.h>

#include "Types.h"
#include "WorkExp.h"

class WorkExpUI : public Gtk::Window {
  public:
    WorkExpUI(Manager*, int, int, UGradApp*, WorkExp*);
    WorkExpUI(Manager*, int, int, GradApp*, WorkExp*);
    ~WorkExpUI();

    Manager*     manager;
    WorkExp*     workExp;

  private:
    void initialize();
    void setWidgets();
    void on_nextOrOtherButton(const Glib::ustring& data);
    void on_backButton(const Glib::ustring& data);
    void on_skipButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);
    void on_saveButton(const Glib::ustring& data);

    // Widgets
    Gtk::Table         createTable;
    Gtk::Label         aLabel, durationLabel, startLabel, endLabel, respLabel;
    Gtk::ComboBoxText  monthCombo, year1Combo, month1Combo, day1Combo, year2Combo, month2Combo, day2Combo;
    Gtk::Entry         respEntry;
    Gtk::Button        nextButton, backButton, otherButton, skipButton, cancelButton, saveButton;

    string day[MAX_BUF], month[MAX_BUF], year[MAX_BUF], duration[MAX_BUF];  

    // 0 = TACourseInfoUI
    // 1 = SelectEntryUI
    // 2 = WorkExpUI
    int prevWin; 

    // 0 = UGrad
    // 1 = Grad
    int stuType; 

    UGradApp* uApp;
    GradApp*  gApp;
    WorkExp*  work;
    bool      addWork;
};

#endif
