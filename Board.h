#ifndef COSC_ASSIGN_TWO_BOARD
#define COSC_ASSIGN_TWO_BOARD
#include <iostream>
#include <vector>
#include <string>


class Board{
public:

    Board(int w, int h);
    void setValues(int x, int y);
    void printBoard();

private:

    int width, height;
    std::string rows;
    std::vector<std::string> test1;
    std::vector<std::vector<std::string> > test2;


};

#endif //COSC_ASSIGN_TWO_BOARD