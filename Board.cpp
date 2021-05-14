#include "Board.h"
#include <iostream>
#include <string>
#include <vector>

Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
  initGrid();
}

Board::Board(std::string boardShapeString, std::string placedTilesString) {
  // Parse board shape string
  // of form "height,width"
  std::string heightString = "";
  std::string buffer = "";
  for (char c : boardShapeString) {
    if (c != ',') {
      buffer += c;
    } else {
      heightString = buffer;
      buffer = "";
    }
  }

  // Create the grid with the parsed dimensions
  width = stoi(buffer);
  height = stoi(heightString);
  initGrid();

  // Parse the placed tiles
  buffer = "";
  Tile* tile = nullptr;
  for (size_t i = 0; i < placedTilesString.length(); i++ ) {
    char c = placedTilesString[i];
    if (c == '@') {
      tile = new Tile(buffer[0], std::stoi(buffer.substr(1, buffer.length())));
      buffer = "";
    } else if (c == ',' || i == placedTilesString.length() - 1) {
      if (i == placedTilesString.length() - 1) {
        buffer.push_back(c);
      }
      addTile(tile, buffer[0], buffer.substr(1, buffer.length()));
      buffer = "";
    } else if (!std::isspace(c)) {
      buffer.push_back(c);
    }
  }
}

Board::~Board() {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      delete getTile(i, j);
    }
  }
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
  std::cout << "\n"
            << "  ";
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

void Board::addTile(Tile *tile, int row, int col) {
  gridVec[row][col] = tile;
}

void Board::addTile(Tile *tile, char row, std::string col) {
  addTile(tile, rowToInt(row), std::stoi(col));
}

std::string Board::toString() {
  std::string placedTilesString = "";
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      if (gridVec[x][y] != nullptr) {
        placedTilesString += gridVec[x][y]->toString() + "@" + rowLabels[x] +
                             std::to_string(y) + ", ";
      }
    }
  }
  placedTilesString =
      placedTilesString.substr(0, placedTilesString.length() - 2);
  return placedTilesString;
}

int Board::getWidth() { return width; }

int Board::getHeight() { return height; }

Tile *Board::getTile(char row, char col) {
  return getTile(rowToInt(row), std::stoi(&col));
}

Tile *Board::getTile(int row, int col) {
  return gridVec[row][col];
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

bool Board::containsPosition(int row, int col) {
  return row >= 0 && row < width && col >= 0 && col < height;
}
