//////////////////////////////////////////////////////////////////////////
// WELCOME UI
// Prompts the user to select if they are a student or an administrator

#include "WelcomeUI.h"
#include "StuOptionUI.h"
#include "AdminOptionUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
WelcomeUI::WelcomeUI(Manager* aManager) 
: aTable(3, 2, false),
  aTitle("Welcome to cuTAES"),
  stuButton("Student"),
  adminButton("Administrator")
{
  manager = aManager;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);

  add(aTable);

  aTable.attach(aTitle, 0, 2, 0, 1,Gtk::EXPAND,Gtk::FILL,0,150);
  aTable.attach(stuButton, 0, 1, 1, 2,Gtk::FILL,Gtk::FILL,40,40);
  aTable.attach(adminButton, 1, 2, 1, 2,Gtk::FILL,Gtk::FILL,40,40);

  stuButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WelcomeUI::on_stuButton), "Student") );
  adminButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WelcomeUI::on_adminButton), "Administrator") );

  show_all_children();

  //cout << "CONSTRUCT WelcomeUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
WelcomeUI::~WelcomeUI() {
  //cout << "DESTRUCT WelcomeUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for student button
void WelcomeUI::on_stuButton(const Glib::ustring& data){ 
  StuOptionUI* stuOptWin = new StuOptionUI(manager);
  stuOptWin->show(); 
}

//////////////////////////////////////////////////////////////////////////
// Event handler for administrator button
void WelcomeUI::on_adminButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
}

