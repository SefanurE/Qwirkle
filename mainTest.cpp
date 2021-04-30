#include "Board.h"
#include <iostream>
#include <string>

int main(void) {
    Board board(20, 14);
    board.printBoard();
    std::cout << "Done" << std::endl;

return EXIT_SUCCESS;
}