#include "Board.h"
#include <iostream>
#include <string>
#include <vector>

/*
 * Constructor Name: Board
 * Purpose: Initalises board dimensions and array to store placed tiles
 * Parameters:
 * width [int] - Width of the board
 * height [int] - Height of the board
 * Return: N/A
 */
Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
  initGrid();
}

/*
 * Constructor Name: Board
 * Purpose: Initalises board dimensions from save and places all previously
 * placed tiles into 2d vector
 * Parameters:
 * boardShapeString [string] - Contains width and height from save
 * placedTilesString [string] - Contains all placed tiles from save
 * Return: N/A
 */
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
  for (size_t i = 0; i < placedTilesString.length(); i++) {
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

/*
 * Deconstructor Name: Board
 * Purpose: Initialises board dimensions from save and places all previously
 * placed tiles into 2d vector
 * Parameters:
 * boardShapeString [string] - Contains width and height from save
 * placedTilesString [string] - Contains all placed tiles from save
 * Return: N/A
 */
Board::~Board() {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      delete getTile(i, j);
    }
  }
}

/*
 * Method Name: initGrid
 * Purpose: Initialises 2d vector based on width and height
 * Parameters: N/A
 * Return: N/A
 */
void Board::initGrid() {
  for (int i = 0; i < height; i++) {
    gridVec.push_back(std::vector<Tile*>(width));
  }
}

/*
 * Method Name: printBoard
 * Purpose: Prints board with all placed tiles
 * Parameters: 
 * coloured [bool] - If colour option was toggled on in menu [true] 
 * or not [false]
 * Return: N/A
 */
void Board::printBoard(bool coloured) {
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
        if (coloured) {
          std::string colourTxt = "";
          if (gridVec[x][y]->getColour() == RED) {
            colourTxt = RED_TXT;
          } else if (gridVec[x][y]->getColour() == ORANGE) {
            colourTxt = ORANGE_TXT;
          } else if (gridVec[x][y]->getColour() == YELLOW) {
            colourTxt = YELLOW_TXT;
          } else if (gridVec[x][y]->getColour() == GREEN) {
            colourTxt = GREEN_TXT;
          } else if (gridVec[x][y]->getColour() == BLUE) {
            colourTxt = BLUE_TXT;
          } else if (gridVec[x][y]->getColour() == PURPLE) {
            colourTxt = PURPLE_TXT;
          }
          std::cout << colourTxt << gridVec[x][y]->toString() 
                      << RESET_TXT << "|";
        } else {
          std::cout << gridVec[x][y]->toString() << "|";
        }
        
      } else {
        std::cout << "  |";
      }
    }
    std::cout << "\n";
  }
}

/*
 * Method Name: addTile
 * Purpose: Adds tile to board at a given position
 * Parameters:
 * tile [Tile*] - Pointer to a tile to add to the board
 * row [int] - Row to place tile in
 * col [int] - Column to place tile in
 * Return: N/A
 */
void Board::addTile(Tile* tile, int row, int col) {
  gridVec[row][col] = tile;
}

/*
 * Method Name: addTile
 * Purpose: Adds tile to board at a given position
 * Parameters:
 * tile [Tile*] - Pointer to a tile to add to the board
 * row [int] - Row to place tile in
 * col [string] - Column to place tile in
 * Return: N/A
 */
void Board::addTile(Tile* tile, char row, std::string col) {
  addTile(tile, rowToInt(row), std::stoi(col));
}

/*
 * Method Name: toString
 * Purpose: Converts all placed tiles to string, used for saving
 * Parameters: N/A
 * Return:
 * string - String containing placed tiles in a valid save format
 */
std::string Board::toString() {
  std::string placedTilesString = "";
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      if (gridVec[x][y] != nullptr) {
        placedTilesString += gridVec[x][y]->toString() + "@" + rowLabels[x]
                             + std::to_string(y) + ", ";
      }
    }
  }
  placedTilesString =
    placedTilesString.substr(0, placedTilesString.length() - 2);
  return placedTilesString;
}

/*
 * Method Name: getWidth
 * Purpose: Retrieves width of board
 * Parameters: N/A
 * Return:
 * int - Width of board
 */
int Board::getWidth() { return width; }

/*
 * Method Name: getHeight
 * Purpose: Retrieves height of board
 * Parameters: N/A
 * Return:
 * int - Height of board
 */
int Board::getHeight() { return height; }

Tile* Board::getTile(char row, char col) {
  return getTile(rowToInt(row), std::stoi(&col));
}

Tile* Board::getTile(int row, int col) {
  return gridVec[row][col];
}

/*
 * Method Name: rowToInt
 * Purpose: Concerts a row character to a row number
 * Parameters:
 * rowLabel [char] - Character to convert
 * Return:
 * int - Int representing the row
 */
int Board::rowToInt(char rowLabel) {
  int index = -1;
  for (size_t i = 0; i < rowLabels.length() && index == -1; i++) {
    if (rowLabels[i] == rowLabel) {
      index = i;
    }
  }
  return index;
}

/*
 * Method Name: intToRow
 * Purpose: Concerts a row number to a row character
 * Parameters:
 * rowLabel [int] - Int to convert
 * Return: string - String representing the row
 */
std::string Board::intToRow(int row) {
  std::string rowLabel = "";
  rowLabel.push_back(rowLabels[row]);
  return rowLabel;
}

/*
 * Method Name: containsPosition
 * Purpose: Checks if a position is within the bounds of the board
 * Parameters:
 * row [int] - Row to check
 * col [int] - Col to check
 * Return:
 * bool - If the position is [true] or is not [false] within the bounds of the
 * board
 */
bool Board::containsPosition(int row, int col) {
  return row >= 0 && row < width && col >= 0 && col < height;
}
