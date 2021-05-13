#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

GameState::GameState(std::string playerNames[PLAYER_COUNT]) {
  players = new Player *[PLAYER_COUNT];
  board = new Board(20, 20);
  bag = new TileBag();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players[i] = new Player(playerNames[i]);
    players[i]->initHand(bag);
  }
  firstTile = true;
  currentPlayerIndex = 0;
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
    players[i]->setScore(stoi(tempPlayerInfoString));

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

  // Display the current players hand and score
  std::cout << std::endl
            << "Your hand is" << std::endl
            << getCurrentPlayer()->getHand()->toString() << std::endl
            << std::endl;
  std::cout << "Current score: " << getCurrentPlayer()->getScore() << std::endl;

  // TODO: remove debug printout here
  std::cout << "BAG CONTAINS " << bag->getList()->toString() << std::endl;
}

bool GameState::doPlaceTile(std::string tileString, std::string position) {
  Player *player = getCurrentPlayer();
  Tile *playedTile = new Tile(tileString[0], tileString[1]);
  bool success = false;
  int tileIndex = player->getHand()->getIndexOf(tileString);

  if (tileIndex != TILE_NOT_FOUND) {
    if (board->getTile(position[0], position[1]) == nullptr) {
      if (firstTile || (!firstTile && validateTile(playedTile, position))) {
        Tile *tile = player->getHand()->remove(tileIndex);
        board->addTile(tile, position[0],
                       position.substr(1, position.length()));
        player->updateScore(1);
        if (bag->getList()->getSize() > 0) {
          player->getHand()->push(bag->draw());
        }
        firstTile = false;
        success = true;
      }
    } else {
      std::cout << "There is already a tile in position " << position << std::endl;
    }
  } else {
    std::cout << "You do not have a " << tileString << " tile!" << std::endl;
  }
  //Next player is called upon a successful end to a round
  if (success) {
    nextPlayer();
  }
  std::cout << "TEST";
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
      // Remove the tile from the players hand and put it in the bag
      bag->getList()->push(hand->remove(tileIndex));
      
      // Draw a tile and put it in the players hand
      hand->insertAfter(tileIndex, bag->draw());

      success = true;
    } else {
      std::cout << "The bag is empty! You cannot replace your tile!"
                << std::endl;
    }
  } else {
    std::cout << "You do not have a " << tile << " tile!" << std::endl;
  }
  //switches to next player after tile replacement (turn used)
  if(success) {
    nextPlayer();
  }

  // Swap player if move was successfull
  if (success) {
    nextPlayer();
  }

  return success;
}

GameState::~GameState() {
  for (int i = 0; i < PLAYER_COUNT; i++) {
    delete players[i];
  }
  delete[] players;
  delete board;
  delete bag;
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

bool GameState::validateTile(Tile *tile, std::string position) {
  // Get row and col from position string
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);

  // Make a set of orthogonal directions
  std::pair<int, int> directions[4] = {
      std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(0, 1),
      std::make_pair(1, 0)};

  int roundScore = 0;
  bool hasNeighbour = false;
  bool validated = true;

  // We scan along each direction to validate the rows
  int distance = 1;
  int direction = 0;
  while (validated && direction < 4) {
    // Determine scan position
    int neebRow = row + directions[direction].first * distance;
    int neebCol = col + directions[direction].second * distance;

    // If we are on the board...
    if (neebCol >= 0 &&
        neebRow >= 0 &&
        neebCol < board->getWidth() &&
        neebRow < board->getHeight()) {
  
      // Get the tile at this position
      Tile *neighbourTile = board->getTile(neebRow, neebCol);

      if (neighbourTile != nullptr) {
        hasNeighbour = true;

        if (!checkPlacementValid(tile, neighbourTile)) {
          std::cout << "You can't place a tile here!" << std::endl;
          validated = false;
        } else {
          distance++;
          if (distance > maxLength) {
            maxLength = distance;
          }
        }
      } else {
        roundScore += distance - 1;
        if (distance == QWIRKLE) {
          roundScore = roundScore + distance;
        }
        direction++;
        distance = 1;
      }
    } else {
      direction++;
      distance = 1;
    }
  }

  bool success = true;
  if (!hasNeighbour || !validated) {
    success = false;
  } else {
    players[0]->updateScore(roundScore);
    std::cout << "max " << maxLength << std::endl;
  }
  return success;
}

bool GameState::checkPlacementValid(Tile *myTile, Tile *neighbourTile) {
  bool colourMatch = neighbourTile->getColour() == myTile->getColour();
  bool shapeMatch = neighbourTile->getShape() == myTile->getShape()-48;
  return ((colourMatch) ^ (shapeMatch));
}
