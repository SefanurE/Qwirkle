#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

GameState::GameState(std::string playerNames[PLAYER_COUNT]) {
  players = new Player *[PLAYER_COUNT];
  board = new Board(BOARD_SIZE, BOARD_SIZE);
  bag = new TileBag();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players[i] = new Player(playerNames[i]);
    players[i]->initHand(bag);
  }
  firstTile = true;
  currentPlayerIndex = 0;
}

GameState::~GameState() {
  for (int i = 0; i < PLAYER_COUNT; i++) {
    delete players[i];
  }
  delete[] players;
  delete board;
  delete bag;
}

GameState::GameState(std::istream &gameData) {
  // Read player information
  players = new Player *[PLAYER_COUNT];
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::string tempPlayerInfoString = "";

    // Read the player name and construct the player
    getline(gameData, tempPlayerInfoString);
    players[i] = new Player(tempPlayerInfoString);

    // Read the player score and set
    getline(gameData, tempPlayerInfoString);
    int score = stoi(tempPlayerInfoString);
    players[i]->setScore(score);

    // Read the players hand and set
    getline(gameData, tempPlayerInfoString);
    players[i]->getHand()->fromString(tempPlayerInfoString);
  }

  // Read board dimensions (height x width)
  std::string boardShapeString = "";
  getline(gameData, boardShapeString);

  // Read placed tiles
  std::string placedTileString = "";
  getline(gameData, placedTileString);

  // Construct the board
  board = new Board(boardShapeString, placedTileString);

  // Read the tile bag and construct it
  std::string tileBagString = "";
  getline(gameData, tileBagString);
  bag = new TileBag(tileBagString);

  // Read the current player then find its index
  std::string currentPlayerName = "";
  getline(gameData, currentPlayerName);
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (players[i]->getName() == currentPlayerName) {
      currentPlayerIndex = i;
    }
  }
}

Player* GameState::getWinningPlayer() {
  Player* winner = nullptr;
  if (bag->getList()->getSize() == 0) {
    for (int i = 0; i < PLAYER_COUNT; i++) {
      if (players[i]->getHand()->getSize() == 0) {
        winner = players[i];
      }
    }
  }

  return winner;
}

void GameState::showAfterGameOutput() {
  std::cout << "Game over" << std::endl;
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::cout << "Score for " << players[i]->getName() << ": ";
    std::cout << std::setfill('0') << std::setw(3) << players[i]->getScore() << std::endl;
  }

  Player* winner = getWinningPlayer();
  std::cout << "Player " << winner->getName() << " won!" << std::endl;
  std::cout << std::endl;
}

void GameState::showBeforeRoundOutput() {
  // Display the current players name
  std::cout << std::endl
            << getCurrentPlayer()->getName() << ", it's your turn" << std::endl;

  // Display all players score
  for (int playerIndex = 0; playerIndex < PLAYER_COUNT; playerIndex++) {
    std::cout << "Score for " << players[playerIndex]->getName() << ": "
              << players[playerIndex]->getScore() << std::endl;
  }

  // Display the board
  board->printBoard();

  // Display the current players hand 
  std::cout << std::endl
            << "Your hand is" << std::endl
            << getCurrentPlayer()->getHand()->toString() << std::endl
            << std::endl;
}

bool GameState::doPlaceTile(std::string tileString, std::string position) {
  // Get row and col from position string
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);

  Player *player = getCurrentPlayer();
  Tile *playedTile = new Tile(
      tileString[0], std::stoi(tileString.substr(1, tileString.length())));

  bool success = false;
  int tileIndex = player->getHand()->getIndexOf(tileString);

  // Do we have the tile?
  if (tileIndex != TILE_NOT_FOUND) {
    // Is the position on the board
    if (board->containsPosition(row, col)) {

      // If the position is empty?
      if (board->getTile(row, col) == nullptr) {
        // Check that this placement is valid
        if (firstTile || validateTile(playedTile, position)) {
          // Remove the tile from the players hand and place it on the board
          Tile *tile = player->getHand()->remove(tileIndex);
          board->addTile(tile, row, col);

          // Award score for this move
          // First tile gets 1 point
          int score = placeTileScore(playedTile, position) + (firstTile ? 1 : 0);
          player->addScore(score);

          // Draw the player a new tile if any remain in the bag
          if (bag->getList()->getSize() > 0) {
            player->getHand()->push(bag->draw());
          }

          firstTile = false;
          success = true;
        }
      } else {
        std::cout << "There is already a tile in position " << position
                  << std::endl;
      }
    } else {
      std::cout << "The position " << position << " isn't on the board"
                << std::endl;
    }
  } else {
    std::cout << "You do not have a " << tileString << " tile!" << std::endl;
  }

  // Next player is called upon a successful end to a round
  if (success) {
    nextPlayer();
  }

  // Cleanup
  delete playedTile;

  return success;
}

Player *GameState::getCurrentPlayer() { return players[currentPlayerIndex]; }

void GameState::nextPlayer() {
  currentPlayerIndex = (currentPlayerIndex + 1) % PLAYER_COUNT;
}

bool GameState::doReplaceTile(std::string tile) {
  // Get the player and their hand
  Player *player = getCurrentPlayer();
  LinkedList *hand = player->getHand();

  // Is the tile in the hand?
  bool success = false;
  int tileIndex = hand->getIndexOf(tile);
  if (tileIndex != TILE_NOT_FOUND) {
    // Is the bag empty?
    if (bag->getList()->getSize() != 0) {
      // Draw a tile and put it in the players hand
      hand->insertAfter(tileIndex, bag->draw());
  
      // Remove the tile from the players hand and put it in the bag
      bag->getList()->push(hand->remove(tileIndex));

      success = true;
    } else {
      std::cout << "The bag is empty! You cannot replace your tile!"
                << std::endl;
    }
  } else {
    std::cout << "You do not have a " << tile << " tile!" << std::endl;
  }

  // Swap player if move was successfull
  if (success) {
    nextPlayer();
  }

  return success;
}

std::string GameState::serialise() {
  std::stringstream ss;

  // Write player info
  for (int i = 0; i < PLAYER_COUNT; i++) {
    ss << players[i]->getName() << std::endl;
    ss << players[i]->getScore() << std::endl;
    ss << players[i]->getHand()->toString() << std::endl;
  }
  // Write board dimension
  ss << board->getHeight() << "," << board->getWidth() << std::endl;

  // Write board tiles
  ss << board->toString() << std::endl;

  // Write tile bag
  ss << bag->getList()->toString() << std::endl;

  // Write current player
  ss << getCurrentPlayer()->getName() << std::endl;

  return ss.str();
}

// Get tiles connected to (tile) in orthogonal direction (dir) in ascending
// distance order.
LinkedList *GameState::getConnectedTilesInDir(Tile *tile, std::string position,
                                              int dir) {
  // Create the list
  LinkedList *tiles = new LinkedList();

  // Get row and col from position string
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);

  // Make a set of orthogonal directions
  std::pair<int, int> directions[4] = {
      std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(0, 1),
      std::make_pair(1, 0)};

  std::pair<int, int> direction = directions[dir];
  int distance = 1;
  bool doScan = true;
  while (doScan) {
    // Determine scan position
    int sRow = row + direction.first * distance;
    int sCol = col + direction.second * distance;

    // Are we are still on the board
    if (!board->containsPosition(sRow, sCol)) {
      doScan = false;
    } else {
      // Get the tile from this position
      Tile *sTile = board->getTile(sRow, sCol);
      if (sTile != nullptr) {
        tiles->push(new Tile(*sTile));
        distance++;
      } else {
        doScan = false;
      }
    }
  }

  return tiles;
}

int GameState::placeTileScore(Tile *tile, std::string position) {
  int roundScore = 0;
  bool gotRowScore = false;
  bool gotColScore = false;

  // For each orthogonal direction (UP, LEFT, DOWN, RIGHT)
  for (int direction = 0; direction < 4; direction++) {
    // Award points for the length of the amount of connected tiles in this direction
    LinkedList *connected = getConnectedTilesInDir(tile, position, direction);
    roundScore += connected->getSize();

    // Get a point for being included in a row?
    if (connected->getSize() != 0) {
      if (direction % 2 == 0 && !gotRowScore) {
        roundScore++;
        gotRowScore = true;
      }

      // Get a point for being included in a col?
      if (direction % 2 == 1 && !gotColScore) {
        roundScore++;
        gotColScore = true;
      }
    }

    // Award double points if the length is a QWIRKLE!!
    if (connected->getSize() == QWIRKLE - 1) {
      roundScore += QWIRKLE;
      std::cout << std::endl << "QWIRKLE!!" << std::endl << std::endl;
    }

    delete connected;
  }

  return roundScore;
}

bool GameState::validateTile(Tile *tile, std::string position) {
  bool valid = true;
  bool hasNeighbour = false;

  // For each orthogonal direction (UP,LEFT,DOWN,RIGHT)
  for (int direction = 0; direction < 4; direction++) {
    // Get all of the connected tiles in this direction
    LinkedList *connected = getConnectedTilesInDir(tile, position, direction);

    // Update whether we have a neighbour
    hasNeighbour = hasNeighbour || connected->getSize() > 0;

    // Validate all of these connected neighbours
    bool doValidate = true;
    for (int i = 0; doValidate && i < connected->getSize(); i++) {
      if (!checkPlacementValid(tile, connected->get(i))) {
        doValidate = false;
        std::cout << "You can't place a " << tile->toString() << " tile here!"
                  << std::endl;
        valid = false;
      }
    }

    delete connected;
  }

  if (!hasNeighbour) {
    std::cout << "You can't place a tile here!" << std::endl;
    valid = false;
  }

  return valid;
}
bool GameState::checkPlacementValid(Tile *myTile, Tile *neighbourTile) {
  bool colourMatch = neighbourTile->getColour() == myTile->getColour();
  bool shapeMatch = neighbourTile->getShape() == myTile->getShape();
  return ((colourMatch) != (shapeMatch));
}
