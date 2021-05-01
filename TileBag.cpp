#include "TileBag.h"
#include <vector>
#include <iostream>
TileBag::TileBag() {
  char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  for (int shape = 0; shape <= 5; shape++) {
    for (int j = 0; j <= 5; j++) {
      tiles.push(new Tile(colours[j], shape));
    }
  }
}

void TileBag::shuffle() {
  srand (time(NULL));
  LinkedList* tempTiles = new LinkedList();
  while (tiles.getSize() != 0) {
    std::cout << "Size: " << tiles.getSize() << std::endl;
    int randIndex = rand() % tiles.getSize();
    std::cout << randIndex << std::endl;
    Tile* tempTile = tiles.remove(randIndex);
    std::cout << "TEST: " << tempTile->toString() << std::endl;
    tempTiles->push(tempTile);
  }
  std::cout << tempTiles->toString() << std::endl;
  tiles = *tempTiles;
}

Tile* TileBag::draw() {
  return tiles.pop();
}

LinkedList TileBag::getList() {
  return tiles;
}