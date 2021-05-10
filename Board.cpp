#include <iostream>
#include <vector>
#include <string>
#include "Board.h"

Board::Board() {

}

Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
  initGrid();
}

Board::Board(std::string boardShapeString, std::string placedTilesString) {
  std::string widthString = "";
  std::string block = "";
  for (char c : boardShapeString) {
    if (c != ',') {
      block += c;
    } else {
      widthString = block;
      block = "";
    }
  }
  width = stoi(widthString);
  height = stoi(block);

  initGrid();

  block = "";
  for (char c : placedTilesString) {
    if (c == ',') {
      for (size_t i = 0; i < block.length(); i++) {
        if (block[i] == '@') {
          Tile* tile = new Tile(block[0], atoi(&block[1]));
          addTile(tile, block[i + 1], block.substr(i + 2, block.length()));
        }
      }
      block = "";
    } else {
      block += c;
    }
  }
}

Board::~Board(){

}

void Board::initGrid() {
  for (int i = 0; i < height; i++) {
    gridVec.push_back(std::vector<Tile*>(width));
  }
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
                if (gridVec[x][y] != nullptr) {
                  std::cout << gridVec[x][y]->toString() << "|";
                } else {
                  std::cout << "  |";
                }
            }
            std::cout << "\n";
        }
    }

void Board::addTile(Tile* tile, char row, std::string col) {
    gridVec[rowToInt(row)][std::stoi(col)] = tile;
}

std::string Board::toString() {
  std::string placedTilesString = "";
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      if (gridVec[x][y] != nullptr) {
        placedTilesString += gridVec[x][y]->toString() + "@" 
                           + rowLabels[x] + std::to_string(y) + ", ";
      }
    }
  }
  placedTilesString = placedTilesString.substr(0, placedTilesString.length() - 2);
  return placedTilesString;
}

int Board::getWidth() {
  return width;
}

int Board::getHeight() {
  return height;
}

Tile* Board::getTile(char row, char col) {
  return getTile(rowToInt(row), std::stoi(&col));
}

Tile* Board::getTile(int row, int col) {
  Tile* tile = nullptr;
  tile = gridVec[row][col];
  return tile;
}

int Board::rowToInt(char rowLabel) {
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int index = -1;
  for (size_t i = 0; i < alphabet.length() && index == -1; i++) {
    if (alphabet[i] == rowLabel) {
      index = i;
    }
  }
  return index;
}
