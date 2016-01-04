//////////////////////////////////////////////////////////////////////////
// TA COURSES INFORMATION WINDOW
// Prompts user to give more information about ta'd courses

#ifndef TACOURSEINFOUI_H
#define TACOURSEINFOUI_H

#include <gtkmm.h>
#include "Types.h"
#include "CourseInfoUI.h"
#include "TACourse.h"

class TACourseInfoUI : public CourseInfoUI {
  public:
    TACourseInfoUI(Manager*, int, int, UGradApp*, TACourse*);
    TACourseInfoUI(Manager*, int, int, GradApp*, TACourse*);
    ~TACourseInfoUI();

    Manager*  manager;

  private:
    void initialize();
    void setWidgets();
    void on_nextButton  (const Glib::ustring& data);
    void on_backButton  (const Glib::ustring& data);
    void on_courseButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);
    void on_saveButton  (const Glib::ustring& data);

    Gtk::Button nextButton, backButton, courseButton, cancelButton, saveButton;

    string    faculty[MAX_BUF];
    TACourse* ta;
    bool      addCrs;
};

#endif

