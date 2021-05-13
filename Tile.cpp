#include "Tile.h"
#include <iostream>
#include <sstream> 
#include <string> 

Tile::Tile(Colour colour, Shape shape) {
  this->colour = colour;
  this->shape = shape;
}

Tile::Tile(Tile& other) {
  this->colour = other.getColour();
  this->shape = other.getShape();
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
