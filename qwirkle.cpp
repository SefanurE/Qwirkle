#include <iostream>

#include "Menu.h"
#include "GameManager.h"

#define EXIT_SUCCESS    0

int main(void) {
  Menu* menu = new Menu();
  menu->mainMenu();
  delete menu;
  return EXIT_SUCCESS;
}
