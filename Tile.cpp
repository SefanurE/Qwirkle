#include "Tile.h"
#include <iostream>
#include <sstream> 
#include <string> 

Tile::Tile(Colour colour, Shape shape) {
  this->colour = colour;
  this->shape = shape;
}

std::string Tile::toString() {
  return colour + std::to_string(shape);
}

Shape Tile::getShape() {
  return shape;
}

Colour Tile::getColour() {
  return colour;
}
