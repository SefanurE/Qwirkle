#ifndef COSC_ASSIGN_TWO_BOARD
#define COSC_ASSIGN_TWO_BOARD
#include <iostream>
#include <vector>
#include <string>


class Board{
public:

    Board(int w, int h);
    ~Board();
    void setValues(int w, int h);
    void printBoard();
    void addTile(Tile tile, int row, int col);
    std::vector<std::string> Board::tileLocations();


private:

    int width, height;
    std::string rowLabels;
    std::vector<std::string> rowVec;
    std::vector<std::vector<std::string> > gridVec;
    std::vector<std::string> tilesOnBoard;



};

#endif //COSC_ASSIGN_TWO_BOARD