#include <iostream>

#include "LinkedList.h"
#include "GameManager.h" // temp

#define EXIT_SUCCESS    0

int main(void) {

   // Test GameManager (temporary)
   GameManager* gm = new GameManager();
   gm->startGame();
   delete gm;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;

}
