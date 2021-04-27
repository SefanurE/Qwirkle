#include <iostream>
#include <vector>
#include <string>

class Board {
    private:
    int width, height;
    std::string rows;
    std::vector<std::string> test1;
    std::vector<std::vector<std::string> > test2;

    public:
    Board(int w, int h) {
        setValues(w, h);
        rows = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        
        for (int i = 0; i < height; i++) {
            test1.push_back("  ");
        }
        //    for (int j = 0; j < width; j++) {
        //        test2[i].push_back("aa");
        //    }
        //}
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
                std::cout << test1[x] << "|";
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