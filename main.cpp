#include "Types.h"
#include "WelcomeUI.h"

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  Manager    manager;
  WelcomeUI  welcomeView(&manager);

  Gtk::Main::run(welcomeView);

  return 0;
}
