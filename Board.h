#ifndef COSC_ASSIGN_TWO_BOARD
#define COSC_ASSIGN_TWO_BOARD
#include <iostream>
#include <vector>
#include <string>

#include "Tile.h"
#include "Board.h"

class Board{
public:

    Board();
    Board(int w, int h);
    ~Board();
    void setValues(int w, int h);
    void printBoard();
    void addTile(Tile tile, int row, int col);
    std::vector<std::string> tileLocations();

private:

    int width, height;
    std::string rowLabels;
    std::vector<std::string> rowVec;
    std::vector<std::vector<std::string> > gridVec;
    std::vector<std::string> tilesOnBoard;
    std::string newTile;



};

#endif //COSC_ASSIGN_TWO_BOARD
