
#include "LinkedList.h"
#include "Menu.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   Menu* menu = new Menu();
   menu->mainMenu();
   delete menu;
   
   return EXIT_SUCCESS;
}
