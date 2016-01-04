///////////////////////////////////////////////////////////////////////////////////////
// ONE REPORT WINDOW
// Shows a list of applications for one course, sorted by applicant's major GPA

#include <fstream>

#include "OneReportUI.h"
#include "SelectCrsUI.h"
#include "AdminOptionUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "CourseQueue.h"
#include "Tools.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
OneReportUI::OneReportUI(Manager* aManager, string crs) 
: summary(8, false, Gtk::SELECTION_NONE)
{
  manager = aManager;
  course = crs;

  set_default_size(1100, 500);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  summary.set_column_title(0, "Student #");
  summary.set_column_title(1, "First Name");
  summary.set_column_title(2, "Last Name");
  summary.set_column_title(3, "E-mail");
  summary.set_column_title(4, "Major/Research");
  summary.set_column_title(5, "Year/Program");
  summary.set_column_title(6, "CGPA/Supervisor");
  summary.set_column_title(7, "Major GPA");

  //cout << "CONSTRUCT OneReportUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
OneReportUI::~OneReportUI() {
  //cout << "DESTRUCT OneReportUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the cancel button
void OneReportUI::on_cancelButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the ListViewText widget with appropriate information
void OneReportUI::fillSummary(int status) {
   int i=0;
   // Find course selected in course queue
  CourseQueue::Node* currCrs = manager->getCourseQueue()->front();

  while(currCrs != 0){
    if (currCrs->data->getName() == course)
      break;
    currCrs = currCrs->next;
  }

  UGradAppQueue* copyU = currCrs->data->getUGradApps();
  GradAppQueue*  copyG = currCrs->data->getGradApps();

  // Add separator for grads
  summary.append("");
  summary.set_text(i, 0, "GRADS");    summary.set_text(i, 1, "--------");
  summary.set_text(i, 2, "--------"); summary.set_text(i, 3, "--------");
  summary.set_text(i, 4, "--------"); summary.set_text(i, 5, "--------");
  summary.set_text(i, 6, "--------"); summary.set_text(i, 7, "--------");
  i++;

  i = fillGradSummary(copyG, i, status);

  // Add separator for undergrads
  summary.append("");
  summary.set_text(i, 0, "UNDERGRADS"); summary.set_text(i, 1, "--------"); 
  summary.set_text(i, 2, "--------");   summary.set_text(i, 3, "--------"); 
  summary.set_text(i, 4, "--------");   summary.set_text(i, 5, "--------"); 
  summary.set_text(i, 6, "--------");   summary.set_text(i, 7, "--------");
  i++;

  fillUGradSummary(copyU, i, status);
}

//////////////////////////////////////////////////////////////////////////
// Fills in the GradApps information
int OneReportUI::fillGradSummary(GradAppQueue* copy, int i, int status) {
  GradAppQueue::Node* currNode;
  currNode = copy->front();

  // If GradQueue is empty
  if (currNode == 0) {
    return i++;
  }  

  copy->sortByResearch();
  currNode = copy->front();

  while (currNode != 0) {
    if (currNode->data->getCourse()->getName() == course) {
      if(currNode->data->getStatus() == status){
        summary.append("");
        summary.set_text(i, 0, currNode->data->getGrad()->getStuNum());
        summary.set_text(i, 1, currNode->data->getGrad()->getFirstName());
        summary.set_text(i, 2, currNode->data->getGrad()->getSurname());
        summary.set_text(i, 3, currNode->data->getGrad()->getEmail());
        summary.set_text(i, 4, currNode->data->getGrad()->getResearch());
        summary.set_text(i, 5, currNode->data->getGrad()->getProgram());
        summary.set_text(i, 6, currNode->data->getGrad()->getSupervisor());
        summary.set_text(i, 7, "");
        i++;
      }
    }
    currNode = currNode->next;
  }
  return i;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the UndergradApps information
void OneReportUI::fillUGradSummary(UGradAppQueue* copy, int i, int status) {
  UGradAppQueue::Node* currNode;
  currNode = copy->front();

  // If UGradQueue is empty
  if (currNode == 0) {
    summary.append("");
    return;
  }  

  copy->sortByMGPA();
  currNode = copy->front();

  while (currNode != 0) {
    if (currNode->data->getCourse()->getName() == course) {
      if(currNode->data->getStatus() == status){
        summary.append("");
        summary.set_text(i, 0, currNode->data->getUndergrad()->getStuNum());
        summary.set_text(i, 1, currNode->data->getUndergrad()->getFirstName());
        summary.set_text(i, 2, currNode->data->getUndergrad()->getSurname());
        summary.set_text(i, 3, currNode->data->getUndergrad()->getEmail());
        summary.set_text(i, 4, currNode->data->getUndergrad()->getMajor());
        summary.set_text(i, 5, Tools::floatToString(currNode->data->getUndergrad()->getYear()));
        summary.set_text(i, 6, Tools::floatToString(currNode->data->getUndergrad()->getCGPA()));
        summary.set_text(i, 7, Tools::floatToString(currNode->data->getUndergrad()->getMGPA()));
        i++;
      }
    }
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Display save dialog
void OneReportUI::saveDialog(){
  Gtk::MessageDialog dialog(*this, "Summary saved."); 
  dialog.run();
}

