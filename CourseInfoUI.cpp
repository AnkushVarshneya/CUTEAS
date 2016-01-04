//////////////////////////////////////////////////////////////////////////
// COURSE INFORMATION UI
// Prompts user to give more information about related courses

#include <fstream>

#include "CourseInfoUI.h"
#include "CourseQueue.h"


//////////////////////////////////////////////////////////////////////////
// Constructor
CourseInfoUI::CourseInfoUI(Manager* aManager, int prev, int type, UGradApp* app)
: createTable(5, 3, false),
  termLabel("Term:"), 
  yearLabel("Year:"),
  uApp(app),
  gApp(0)
{
  manager = aManager;
  prevWin = prev;
  stuType = type;
  count = 0;
  initialize();
}

//////////////////////////////////////////////////////////////////////////
// Constructor
CourseInfoUI::CourseInfoUI(Manager* aManager, int prev, int type, GradApp* app) 
: createTable(5, 3, false),
  termLabel("Term:"), 
  yearLabel("Year:"),
  uApp(0),
  gApp(app)
{
  manager = aManager;
  prevWin = prev;
  stuType = type;
  count = 0;
  initialize();
}

//////////////////////////////////////////////////////////////////////////
// Initialize
//   Extension of the constructor
void CourseInfoUI::initialize() {
  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);
  add(createTable);

  // Fill course combo box
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();
  while (currNode != 0){ 
    courseCombo.append(currNode->data->getName());
    currNode = currNode->next;
  }
  courseCombo.set_active(0);

  // Read from file using getline function
  ifstream infile("info.txt", ios::in);
  if (!infile) {
    cout << "Could not open file" << endl;
  }
  while (!infile.eof()) {
    getline(infile, info[count]);
    count++;
  }
  
  int j;
  //Fill the combo
  for (i=0, j=0; i<(count-1); i++, j++){
    if(info[i] != "~") {
       termCombo.append(info[i]);
       term[j] = info[i];
    }
    else break;
  }
  for(i= i+1, j=0; i <(count -1); i++, j++){
    if(info[i] != "~") {
      yearCombo.append(info[i]);
      year[j] = info[i];
    }
    else break;
  }

  termCombo.set_active(0);
  yearCombo.set_active(0);

  createTable.attach(aLabel, 0, 2, 0, 1, Gtk::FILL,Gtk::FILL, 0, 42);
  createTable.attach(courseCombo, 2, 3, 0, 1, Gtk::FILL,Gtk::FILL, 10, 30);
  createTable.attach(termLabel, 0, 1, 1, 2);
  createTable.attach(termCombo, 1, 3, 1, 2, Gtk::FILL,Gtk::FILL,75, 20); 
  createTable.attach(yearLabel, 0, 1, 2, 3);
  createTable.attach(yearCombo, 1, 3, 2, 3, Gtk::FILL,Gtk::FILL,75, 20); 
  createTable.attach(finalLabel, 0, 1, 3, 4);
  createTable.attach(finalCombo, 1, 3, 3, 4, Gtk::FILL,Gtk::FILL,75, 20); 

  show_all_children();

  //cout << "CONSTRUCT CourseInfoUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
CourseInfoUI::~CourseInfoUI() {
  //cout << "DESTRUCT CourseInfoUI" << endl;
}

