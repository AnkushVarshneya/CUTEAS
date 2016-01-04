///////////////////////////////////////////////////////////////////////////////////////
// ALL REPORTS WINDOW
// Shows a list of applications for all courses
//   sorted by applicant's major GPA or research area

#include <fstream>

#include "AllReportsUI.h"
#include "AdminOptionUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "CourseQueue.h"
#include "Tools.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
AllReportsUI::AllReportsUI(Manager* aManager) 
: summary(10, false, Gtk::SELECTION_NONE)
{
  manager = aManager;

  set_default_size(1200, 500);
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  summary.set_column_title(0, "Course");
  summary.set_column_title(1, "UGrad/Grad");
  summary.set_column_title(2, "Student #");
  summary.set_column_title(3, "First Name");
  summary.set_column_title(4, "Last Name");
  summary.set_column_title(5, "E-mail");
  summary.set_column_title(6, "Major/Research");
  summary.set_column_title(7, "Year/Program");
  summary.set_column_title(8, "CGPA/Supervisor");
  summary.set_column_title(9, "Major GPA");

  //cout << "CONSTRUCT AllReportsUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
AllReportsUI::~AllReportsUI() {
  //cout << "DESTRUCT AllReportsUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void AllReportsUI::on_backButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the cancel button
void AllReportsUI::on_cancelButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the ListViewText widget with appropriate information
void AllReportsUI::fillSummary(int status) {
  int i = 0;
  bool added = false;

  // Go through all the courses
  CourseQueue::Node* currCrs = manager->getCourseQueue()->front();

  while(currCrs != 0){
    UGradAppQueue* copyU = currCrs->data->getUGradApps();
    UGradAppQueue::Node* currUNode;
  
    GradAppQueue*  copyG = currCrs->data->getGradApps();
    GradAppQueue::Node* currGNode;

    // Add separator for each course if a course was just added to summary
    if (added == true) {
      summary.append("");
      summary.set_text(i, 0, "--------"); summary.set_text(i, 1, "--------");
      summary.set_text(i, 2, "--------"); summary.set_text(i, 3, "--------");
      summary.set_text(i, 4, "--------"); summary.set_text(i, 5, "--------");
      summary.set_text(i, 6, "--------"); summary.set_text(i, 7, "--------");
      summary.set_text(i, 8, "--------"); summary.set_text(i, 9, "--------");
      i++;
      added = false;
    }

    // If GradAppQueue isn't empty
    if (copyG->front() != 0) { 
      copyG->sortByResearch();
      currGNode = copyG->front();

      while (currGNode != 0) {
        if (currGNode->data->getStatus() == status){
	  summary.append("");
	  summary.set_text(i, 0, currGNode->data->getCourse()->getName());
	  summary.set_text(i, 1, "GRAD");
	  summary.set_text(i, 2, currGNode->data->getGrad()->getStuNum());
	  summary.set_text(i, 3, currGNode->data->getGrad()->getFirstName());
          summary.set_text(i, 4, currGNode->data->getGrad()->getSurname());
	  summary.set_text(i, 5, currGNode->data->getGrad()->getEmail());
          summary.set_text(i, 6, currGNode->data->getGrad()->getResearch());
	  summary.set_text(i, 7, currGNode->data->getGrad()->getProgram());
	  summary.set_text(i, 8, currGNode->data->getGrad()->getSupervisor());
	  summary.set_text(i, 9, "");
	  i++;
          added = true;
        }
        currGNode = currGNode->next;
      }
    }

    // If UGradAppQueue isn't empty
    if (copyU->front() != 0) {
      copyU->sortByMGPA();
      currUNode = copyU->front();
      while (currUNode != 0) {
        if (currUNode->data->getStatus() == status){
	  summary.append("");   
	  summary.set_text(i, 0, currUNode->data->getCourse()->getName());
	  summary.set_text(i, 1, "UGRAD");
	  summary.set_text(i, 2, currUNode->data->getUndergrad()->getStuNum());
	  summary.set_text(i, 3, currUNode->data->getUndergrad()->getFirstName());
	  summary.set_text(i, 4, currUNode->data->getUndergrad()->getSurname());
	  summary.set_text(i, 5, currUNode->data->getUndergrad()->getEmail());
	  summary.set_text(i, 6, currUNode->data->getUndergrad()->getMajor());
	  summary.set_text(i, 7, Tools::floatToString(currUNode->data->getUndergrad()->getYear()));
	  summary.set_text(i, 8, Tools::floatToString(currUNode->data->getUndergrad()->getCGPA()));
	  summary.set_text(i, 9, Tools::floatToString(currUNode->data->getUndergrad()->getMGPA()));
	  i++;
          added = true;
        } 
        currUNode = currUNode->next; 
      }
    }
    currCrs = currCrs->next;
  }

  // If there are no matches
/*  if (i == 0)
    summary.append("There are no applications.");
*/
}

//////////////////////////////////////////////////////////////////////////
// Display saved dialog
void AllReportsUI::saveDialog(){
  Gtk::MessageDialog dialog(*this, "Summary saved."); 
  dialog.run();
}

