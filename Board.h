#ifndef COSC_ASSIGN_TWO_BOARD
#define COSC_ASSIGN_TWO_BOARD
#include <iostream>
#include <vector>
#include <string>
#include "Tile.h"
#include "Board.h"

class Board {
public:
    Board(int width, int height);
    Board(std::string boardShapeString, std::string placedTilesString);
    ~Board();
    void printBoard();
    void addTile(Tile* tile, char col, std::string row);
    Tile* getPosition(char row, char col);
    int getWidth();
    int getHeight();
    std::string toString();

private:

    int width, height;
    const std::string rowLabels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::vector<Tile*>> gridVec;
    int rowToInt(char columnLabel);
    void initGrid();
};

#endif //COSC_ASSIGN_TWO_BOARD
