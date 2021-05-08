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

void Board::addTile(Tile* tile, int row, int col) {
    newTile = tile->toString();
    gridVec[col][row] = newTile;
    tilesOnBoard.push_back(newTile + "@" + std::to_string(row) + std::to_string(col));
}

std::vector<std::string> Board::tileLocations() {
    return tilesOnBoard;
}

void Board::fromString(std::string placedTileString) {
  char tileColor = ' ';
  std::string tileShape = "";
  std::string column = "";
  std::string row = "";
  for (char c : placedTileString) {
    if (c != ',' && c != ' ') {
      if (tileColor == ' ') {
        tileColor = c;
      } else if (tileShape.empty()) {
        tileShape = c;
      } else if (column.empty()) {
        column = c;
      } else {
        row = c;
        Tile* newTile = new Tile(tileColor, stoi(tileShape));
        addTile(newTile, stoi(row), stoi(column));
        tileColor = ' ';
        tileShape = "";
        column = "";
        row = "";
      }
    }
  }
}

std::string Board::toString() {
  std::string boardString = "";
  for (size_t i = 0; i < tilesOnBoard.size(); i++) {
    boardString += tilesOnBoard[i];
    if (i != tilesOnBoard.size() - 1) {
      boardString += ", ";
    }
  }
  return boardString;
}

int Board::getWidth() {
  return width;
}

int Board::getHeight() {
  return height;
}
