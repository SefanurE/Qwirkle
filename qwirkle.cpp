#include <iostream>

#include "Menu.h"
#include "GameManager.h"

#define EXIT_SUCCESS    0

int main(void) {
  TileBag* bag = new TileBag();
  std::cout << bag->getList()->toString() << std::endl;
  bag->shuffle();
  std::cout << bag->getList()->toString() << std::endl;
  return EXIT_SUCCESS;
}
