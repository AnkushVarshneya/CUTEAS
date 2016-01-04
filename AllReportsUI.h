///////////////////////////////////////////////////////////////////////////////////////
// ALL REPORTS WINDOW
// Shows a list of applications for all courses
//   sorted by applicant's major GPA or research area

#ifndef ALLREPORTSUI_H 
#define ALLREPORTSUI_H

#include "Types.h"
#include <gtkmm.h>

class AllReportsUI : public Gtk::Window {
  public:
    AllReportsUI(Manager*);
    ~AllReportsUI();

    Manager* manager;

    void on_backButton(const Glib::ustring& data);
    void on_cancelButton(const Glib::ustring& data);
    void fillSummary(int);
    void saveDialog();

    Gtk::ListViewText summary;
};

#endif
