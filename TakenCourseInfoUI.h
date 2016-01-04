//////////////////////////////////////////////////////////////////////////
// TAKEN COURSES INFORMATION WINDOW
// Prompts user to give more information about taken courses

#ifndef TAKENCOURSEINFOUI_H
#define TAKENCOURSEINFOUI_H

#include <gtkmm.h>
#include "Types.h"
#include "CourseInfoUI.h"
#include "TakenCourse.h"

class TakenCourseInfoUI : public CourseInfoUI {
  public:
    TakenCourseInfoUI(Manager*, int, int, UGradApp*, TakenCourse*);
    ~TakenCourseInfoUI();

  private:
    void setWidgets();
    void on_nextButton  (const Glib::ustring& data);
    void on_backButton  (const Glib::ustring& data);
    void on_courseButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);
    void on_saveButton  (const Glib::ustring& data);

    Gtk::Button nextButton, backButton, courseButton, cancelButton, saveButton;

    string       final[MAX_BUF];
    TakenCourse* taken;
    bool         addCrs;
};

#endif

