#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
  this->colour = colour;
  this->shape = shape;
}

std::string Tile::toString() {
  return std::to_string(shape) + colour;
}
