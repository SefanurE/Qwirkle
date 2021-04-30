#include <iostream>

#include "LinkedList.h"
#include "Menu.h"
#include "GameManager.h" // temp

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   Menu* menu = new Menu();
   menu->mainMenu();
   delete menu;
   
   // Test GameManager (temporary)
   GameManager* gm = new GameManager();
   gm->startGame();
   delete gm;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
