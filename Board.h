#ifndef COSC_ASSIGN_TWO_BOARD
#define COSC_ASSIGN_TWO_BOARD

#include <iostream>
#include <vector>
#include <string>
#include "Tile.h"

class Board {
  public:
    Board();
    Board(int width, int height);
    Board(std::string boardShapeString, std::string placedTilesString);
    ~Board();
    void printBoard();
    void addTile(Tile* tile, char row, std::string col);
    void addTile(Tile* tile, int row, int col);
    Tile* getTile(int row, int col);
    Tile* getTile(char row, char col);
    int getWidth();
    int getHeight();
    std::string toString();
    bool containsPosition(int row, int col);
    int rowToInt(char rowLabel);

  private:
    int width, height;
    const std::string rowLabels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::vector<Tile*>> gridVec;
    void initGrid();
};

#endif //COSC_ASSIGN_TWO_BOARD
