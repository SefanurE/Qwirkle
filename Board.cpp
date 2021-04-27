#include <iostream>
#include <vector>
#include <string>

class Board {
    private:
    int width, height;
    std::string rows;

    public:
    Board(int w, int h) {
        setValues(w, h);
        rows = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    void setValues(int x, int y) {
        width = x;
        height = y;
    }

    void printBoard() {
        std::cout << " ";
        for (int a = 0; a < width; a++) {
            if (a < 11) {
                std::cout << "  " << a;
            } else {
                std::cout << " " << a;
            }
            
        }
        std::cout << "\n" << "  ";
        for (int a = 0; a < width; a++) {
            std::cout << "---";
        }
        std::cout << "-\n";
        for (int x = 0; x < height; x++) {
            std::cout << rows[x] << " |";
            for (int y = 0; y < width; y++) {
                std::cout << "  " << "|";
            }
            std::cout << "\n";
        }
    }
};


int main () {
    Board board(26, 26);
    board.printBoard();
    return 0;
}