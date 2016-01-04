///////////////////////////////////////////////////////////////////////////////////////
// ONE REPORT WINDOW
// Shows a list of applications for one course, sorted by applicant's major GPA

#ifndef ONEREPORTUI_H 
#define ONEREPORTUI_H

#include "Types.h"
#include <gtkmm.h>

class GradAppQueue;
class UGradAppQueue;

class OneReportUI : public Gtk::Window {
  public:
    OneReportUI(Manager*, string);
    ~OneReportUI();

    Manager* manager;

    void on_cancelButton(const Glib::ustring& data);
    void fillSummary(int);
    void fillUGradSummary(UGradAppQueue*, int, int);
    int  fillGradSummary(GradAppQueue*, int, int);
    void saveDialog();

    Gtk::ListViewText   summary;

    string course;
};

#endif
