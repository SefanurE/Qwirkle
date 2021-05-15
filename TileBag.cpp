#include "TileBag.h"
#include <vector>
#include <iostream>

TileBag::TileBag() {
  tiles = new LinkedList();
  char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  for (int shape = 0; shape < SHAPES_COUNT; shape++) {
    for (int colour = 0; colour < COLOURS_COUNT; colour++) {
      tiles->push(new Tile(colours[colour], shape));
      tiles->push(new Tile(colours[colour], shape));
    }
  }
  shuffle();
}

TileBag::TileBag(std::string tileBagString) {
  tiles = new LinkedList();
  std::string buffer = "";
  for (size_t i = 0; i < tileBagString.length(); i++) {
    char c = tileBagString[i];
    if (c != ',') {
      buffer.push_back(c);
    } else {
      Tile* tile = new Tile(buffer[0], std::stoi(buffer.substr(1, buffer.length())));
      tiles->push(tile);
      buffer = "";
    }
  }
}

TileBag::~TileBag() {
  delete tiles;
}

void TileBag::shuffle() {
  srand (time(NULL));
  LinkedList* newTiles = new LinkedList();
  while (tiles->getSize() != 0) {
    int randIndex = rand() % tiles->getSize();
    Tile* tempTile = tiles->remove(randIndex);
    newTiles->push(new Tile(*tempTile));
    delete tempTile;
  }
  delete tiles;
  tiles = newTiles;
}

Tile* TileBag::draw() {
  return tiles->pop();
}

LinkedList* TileBag::getList() {
  return tiles;
}
