
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {

  // Tile Test
  Tile* tile1 = new Tile(RED, CIRCLE);
  Tile* tile2 = new Tile(ORANGE, STAR_4);
  Tile* tile3 = new Tile(YELLOW, DIAMOND);
  Tile* tile4 = new Tile(GREEN, SQUARE);
  Tile* tile5 = new Tile(BLUE, STAR_6);
  Tile* tile6 = new Tile(PURPLE, CLOVER);
  std::cout << tile1->toString() << std::endl;
  std::cout << tile2->toString() << std::endl;
  std::cout << tile3->toString() << std::endl;
  std::cout << tile4->toString() << std::endl;
  std::cout << tile5->toString() << std::endl;
  std::cout << tile6->toString() << std::endl;

  // LinkedList Test
  LinkedList* list = new LinkedList();
  list->push(tile1);
  list->push(tile2);
  list->push(tile3);
  list->push(tile4);
  list->push(tile5);
  list->push(tile6);
  list->remove(10);
  std::cout << list->toString() << std::endl;

  return EXIT_SUCCESS;
}
