#include <iostream>
#include <vector>
#include <string>
#include "Board.h"

Board::Board(int w, int h) {
        setValues(w, h);
        rowLabels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                rowVec.push_back("  ");
            }
            gridVec.push_back(rowVec);
        }
}

Board::~Board(){
}


void Board::setValues(int w, int h) {
    width = w;
    height = h;
}

void Board::printBoard() {
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
            std::cout << rowLabels[x] << " |";
            for (int y = 0; y < width; y++) {
                std::cout << gridVec[x][y] << "|";
            }
            std::cout << "\n";
        }
    }

void Board::addTile(Tile tile, int row, int col) {
    newTile = tile.toString();
    gridVec[col][row] = newTile;
    tilesOnBoard.push_back(newTile + "@" + std::to_string(row) + std::to_string(col));

}

std::vector<std::string> Board::tileLocations() {
    return tilesOnBoard;
}
