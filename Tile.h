#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
  private:
    Colour colour;
    Shape  shape;

  public:
    Tile(Colour colour, Shape shape);
    Tile(Tile& other);
    std::string toString(bool coloured);
    Shape getShape();
    Colour getColour();
};

#endif // ASSIGN2_TILE_H
