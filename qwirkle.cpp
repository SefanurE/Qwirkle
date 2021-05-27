#include <iostream>

#include "Menu.h"
#include "GameManager.h"

#define EXIT_SUCCESS    0

int main(int argc, char** argv) {
  int numPlayers = 2;
  bool multiPlace = false;
  if (argc > 2) {
    std::cerr << "Invalid game options" << std::endl;
  } else if (argc == 2) {
    std::string argument = argv[1];
    if (argument == CLA_3_PLAYERS) {
      numPlayers = 3;
    } else if (argument == CLA_4_PLAYERS) {
      numPlayers = 4;
    } else if (argument == CLA_MULTI_PLACE) {
      multiPlace = true;
    } else {
      std::cerr << "Invalid game options" << std::endl;
    }
  }
  Menu* menu = new Menu();
  menu->mainMenu(numPlayers, multiPlace);
  delete menu;
  return EXIT_SUCCESS;
}
