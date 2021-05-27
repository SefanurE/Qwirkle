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

std::string Tile::toDisplayString(bool coloured) {
  std::string tileString = colour + std::to_string(shape);
  if (coloured) {
    std::string escape = "";
    if (colour == RED) {
      escape = RED_ESCAPE;
    } else if (colour == ORANGE) {
      escape = ORANGE_ESCAPE;
    } else if (colour == YELLOW) {
      escape = YELLOW_ESCAPE;
    } else if (colour == GREEN) {
      escape = GREEN_ESCAPE;
    } else if (colour == BLUE) {
      escape = BLUE_ESCAPE;
    } else if (colour == PURPLE) {
      escape = PURPLE_ESCAPE;
    }
    tileString = escape + tileString + RESET_ESCAPE;
  }
  return tileString;
}

Shape Tile::getShape() {
  return shape;
}

Colour Tile::getColour() {
  return colour;
}
