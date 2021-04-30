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

private:

    int width, height;
    std::string rowLabels;
    std::vector<std::string> rowVec;
    std::vector<std::vector<std::string> > gridVec;


};

#endif //COSC_ASSIGN_TWO_BOARD