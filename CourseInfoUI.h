//////////////////////////////////////////////////////////////////////////
// COURSE INFORMATION UI
// Prompts user to give more information about related courses

#ifndef COURSEINFOUI_H
#define COURSEINFOUI_H

#include <gtkmm.h>
#include "Types.h"

class CourseInfoUI : public Gtk::Window {
  public:
    CourseInfoUI(Manager*, int, int, UGradApp*);
    CourseInfoUI(Manager*, int, int, GradApp*);
    ~CourseInfoUI();

    Manager*  manager;

    Gtk::Table         createTable;
    Gtk::Label         aLabel, yearLabel, termLabel, finalLabel;
    Gtk::ComboBoxText  yearCombo, termCombo, finalCombo, courseCombo;

    // 0 = FormUI;
    // 1 = TakenCourseInfoUI; 
    // 2 = TACourseInfoUI; 
    // 3 = SelectEntryUI; 
    // 4 = WorkExpUI
    int prevWin; 

    // 0 = UGrad; 
    // 1 = Grad;
    int stuType;
    
    string info[MAX_BUF], term[MAX_BUF], year[MAX_BUF];
    int i, count;   // Keep these for inherited classes to fill in their widgets

    UGradApp* uApp;
    GradApp*  gApp;

  private:
    void initialize();
};

#endif

