#include "TileBag.h"
#include <vector>
#include <iostream>
TileBag::TileBag() {
  tiles = new LinkedList();
  char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  for (int shape = 0; shape <= 5; shape++) {
    for (int j = 0; j <= 5; j++) {
      tiles->push(new Tile(colours[j], shape));
      tiles->push(new Tile(colours[j], shape));
    }
  }
  shuffle();
}

TileBag::TileBag(std::string tileBagString) {
  tiles = new LinkedList();
  std::string block = "";
  for (char c : tileBagString) {
    if (c != ',') {
      block += c;
    } else {
      Tile* newTile = new Tile(block[0], atoi(&block[1]));
      std::cout << newTile->toString() << std::endl;
      tiles->push(newTile);
      block = "";
    }
  }
  Tile* newTile = new Tile(block[0], atoi(&block[1]));
  tiles->push(newTile);
  shuffle();
}

void TileBag::shuffle() {
  srand (time(NULL));
  LinkedList* tempTiles = new LinkedList();
  while (tiles->getSize() != 0) {
    int randIndex = rand() % tiles->getSize();
    Tile* tempTile = tiles->remove(randIndex);
    tempTiles->push(tempTile);
  }
  tiles = tempTiles;
}

Tile* TileBag::draw() {
  return tiles->pop();
}

LinkedList* TileBag::getList() {
  return tiles;
}
