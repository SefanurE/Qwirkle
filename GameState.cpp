#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

/*
 * Constructor Name: GameState
 * Purpose: Initalises all structures required for gameplay to their default
 * values
 * Parameters:
 * playerNames [string*] - Array of player names to initialise players with
 * Return: N/A
 */
GameState::GameState(std::vector<std::string> playerNames, bool multiPlace) {
  numPlayers = playerNames.size();
  this->multiPlace = multiPlace;
  players = new Player* [numPlayers];
  board = new Board(BOARD_SIZE, BOARD_SIZE);
  bag = new TileBag();
  for (int i = 0; i < numPlayers; i++) {
    players[i] = new Player(playerNames[i]);
    players[i]->initHand(bag);
  }
  firstTile = true;
  currentPlayerIndex = 0;
}

/*
 * Deconstructor Name: GameState
 * Purpose: Cleans up all structures required for gameplay
 * Parameters: N/A
 * Return: N/A
 */
GameState::~GameState() {
  for (int i = 0; i < numPlayers; i++) {
    delete players[i];
  }
  delete[] players;
  delete board;
  delete bag;
}

/*
 * Constructor Name: GameState
 * Purpose: Instantiates a new gameState with the data contained in the gameData
 * reference. Creates all players and updates state of board to last save/
 * Parameters:
 * gameData [istream] - A reference to the gameData istream
 */
GameState::GameState(std::istream& gameData, int numPlayers, bool multiPlace) {
  // Read player information
  players = new Player* [numPlayers];
  this->numPlayers = numPlayers;
  this->multiPlace = multiPlace;
  // Clean through first 2 lines if numPlayers was part of the save file
  for (int i = 0; i < numPlayers; i++) {
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

  // If we have no tiles then we can place anywhere
  firstTile = placedTileString.length() == 0;

  // Construct the board
  board = new Board(boardShapeString, placedTileString);

  // Read the tile bag and construct it
  std::string tileBagString = "";
  getline(gameData, tileBagString);
  bag = new TileBag(tileBagString);

  // Read the current player then find its index
  std::string currentPlayerName = "";
  getline(gameData, currentPlayerName);
  for (int i = 0; i < numPlayers; i++) {
    if (players[i]->getName() == currentPlayerName) {
      currentPlayerIndex = i;
    }
  }
}

/*
 * Method Name: isGameOver()
 * Purpose: Determine whether the game is over.
 */
bool GameState::isGameOver() {
  // Is the game over?
  bool gameOver = false;
  if (bag->getList()->getSize() == 0) {
    for (int i = 0; !gameOver && i < numPlayers; i++) {
      if (players[i]->getHand()->getSize() == 0) {
        gameOver = true;
      }
    }
  }

  return gameOver;
}


/*
 * Method Name: getWinningPlayer()
 * Purpose: Returns the player with the highest score if there is one
 * and the game is over.
 */
Player* GameState::getWinningPlayer() {
  Player* winner = nullptr;

  // Is the game over?
  if (isGameOver()) {
    // Get player w/ highest score (if there is one)
    bool isDraw = false;
    winner = players[0];
    for (int i = 1; !isDraw && i < numPlayers; i++) {
      if (players[i]->getScore() == winner->getScore()) {
        winner = nullptr;
        isDraw = true;
      } else if (players[i]->getScore() > winner->getScore()) {
        winner = players[i];
      }
    }
  }

  return winner;
}

/*
 * Method Name: showAfterGameOutput
 * Purpose: Displays post game information such as final player scores and
 * winning player
 * Parameters: N/A
 * Return: void
 */
void GameState::showAfterGameOutput() {
  std::cout << "Game over" << std::endl;
  for (int i = 0; i < numPlayers; i++) {
    std::cout << "Score for " << players[i]->getName() << ": ";
    std::cout << std::setfill('0') << std::setw(3) << players[i]->getScore() 
              << std::endl;
  }

  Player* winner = getWinningPlayer();
  if (winner != nullptr) {
    std::cout << "Player " << winner->getName() << " won!" << std::endl;
  }
  std::cout << std::endl;
}

/*
 * Method Name: showBeforeRoundOutput
 * Purpose: Displays player scores, current state of board and current players
 * hand.
 * Parameters: N/A
 * Return: void
 */
void GameState::showBeforeRoundOutput() {
  // Display the current players name
  std::cout << std::endl
            << getCurrentPlayer()->getName() << ", it's your turn" << std::endl;

  // Display all players score
  for (int playerIndex = 0; playerIndex < numPlayers; playerIndex++) {
    std::cout << "Score for " << players[playerIndex]->getName() << ": "
              << players[playerIndex]->getScore() << std::endl;
  }

  // Display the board
  board->printBoard();

  // Display the current players hand 
  std::cout << std::endl
            << "Your hand is" << std::endl
            << getCurrentPlayer()->getHand()->toString(true) << std::endl
            << std::endl;
}

/*
 * Method Name: doPlaceTile
 * Purpose: Validates both the desired location and tile the user wants to place
 * If valid, moves the tile from the players hand to the board and updates
 * score. Otherwise notifies player of invalid move.
 * Parameters:
 * tileString [string] - Tile the player wants to place on the board
 * position [string] - Desired position in which to place the tile
 * Return: bool - If the tile was successfully placed [true] or not [false]
 */
bool GameState::doPlaceTile(std::string tileString, std::string position) {
  // Get row and col from position string
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);

  Player* player = getCurrentPlayer();
  Tile* playedTile = new Tile(
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
          Tile* tile = player->getHand()->remove(tileIndex);
          board->addTile(tile, row, col);

          // Award score for this move
          // First tile gets 1 point
          int score = placeTileScore(playedTile, position) 
                                     + (firstTile ? 1 : 0);
          player->addScore(score);

          placedTilesOnTurn += 1;

          if (!multiPlace || player->getHand()->getSize() == 0) {
            nextPlayer();
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

  // Cleanup
  delete playedTile;

  return success;
}

/*
 * Method Name: getCurrentPlayer
 * Purpose: Retrieve the current player
 * Parameters: N/A
 * Return: Player* - Pointer to the current player
 */
Player* GameState::getCurrentPlayer() {
  return players[currentPlayerIndex];
}

/*
 * Method Name: nextPlayer
 * Purpose: Move currentPlayerIndex to the next player
 * Parameters: N/A
 * Return: N/A
 */
void GameState::nextPlayer() {
  for (int i = 0; i < placedTilesOnTurn; i++) {
    if (bag->getList()->getSize() > 0) {
      getCurrentPlayer()->getHand()->push(bag->draw());
    }
  }
  currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
  placedTilesOnTurn = 0;
}

/*
 * Method Name: doReplaceTile
 * Purpose: Check if the player has a given tile on their hand and there are
 * tiles remaining in the bag. If so, replace their tile with a new tile and
 * return theirs to the bag. Otherwise notifies the player of an invalid move
 * Parameters:
 * tile [string] - The tile the player wishes to replace
 * Return:
 * bool - If the the attempt to replace the tile was successful [true] or not
 * [false]
 */
bool GameState::doReplaceTile(std::string tile) {
  bool success = false;
  if (placedTilesOnTurn == 0) {
    // Get the player and their hand
    Player* player = getCurrentPlayer();
    LinkedList* hand = player->getHand();

    // Is the tile in the hand?
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

    // Swap player if move was successful
    if (success) {
      nextPlayer();
    }
  } else {
    std::cout << "You have already placed a tile this around" << std::endl;
  }
  return success;
}

bool GameState::doEndTurn() {
  bool success = false;
  if (placedTilesOnTurn != 0 || !multiPlace) {
    nextPlayer();
    success = true;
  } else {
    std::cout << "You must do 1 action before ending your turn" << std::endl;
  }
  return success;
}

/*
 * Method Name: serialise
 * Purpose: Converts all game data into a string stream to be saved to a file
 * Parameters:
 * Return:
 * string - All important gamedata in the correct save format
 */
std::string GameState::serialise() {
  std::stringstream ss;

  // Write player info
  for (int i = 0; i < numPlayers; i++) {
    ss << players[i]->getName() << std::endl;
    ss << players[i]->getScore() << std::endl;
    ss << players[i]->getHand()->toString(false) << std::endl;
  }
  // Write board dimension
  ss << board->getHeight() << "," << board->getWidth() << std::endl;

  // Write board tiles
  ss << board->toString() << std::endl;

  // Write tile bag
  ss << bag->getList()->toString(false) << std::endl;

  // Write current player
  ss << getCurrentPlayer()->getName() << std::endl;

  return ss.str();
}

/*
 * Method Name: getConnectedTilesInDir
 * Purpose: Get tiles connected to (tile) in orthogonal direction (dir) in
 * ascending distance order.
 * Parameters:
 * tile [Tile*] -
 * position [string] -
 * dir [int] -
 * Return:
 * LinkedList* -
 */
LinkedList* GameState::getConnectedTilesInDir(Tile* tile, std::string position,
  int dir) {
  // Create the list
  LinkedList* tiles = new LinkedList();

  // Get row and col from position string
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);

  // Make a set of orthogonal directions
  std::pair<int, int> directions[4] = {
    std::make_pair(0, -1), std::make_pair(-1, 0),
    std::make_pair(0, 1),  std::make_pair(1, 0) };

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
      Tile* sTile = board->getTile(sRow, sCol);
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

/*
 * Method Name: placeTileScore
 * Purpose: Get tiles connected to (tile) in orthogonal direction (dir) in
 * ascending distance order.
 * Parameters:
 * tile [Tile*] -
 * position [string] -
 * dir [int] -
 * Return:
 * LinkedList* -
 */
int GameState::placeTileScore(Tile* tile, std::string position) {
  int roundScore = 0;
  bool gotRowScore = false;
  bool gotColScore = false;

  // For each orthogonal direction (UP, LEFT, DOWN, RIGHT)
  for (int direction = 0; direction < 4; direction++) {
    // Award points for the length of the amount of connected tiles in this 
    // direction
    LinkedList* connected = getConnectedTilesInDir(tile, position, direction);
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

/*
 * Method Name: validateTile
 * Purpose: Checks if a tile can be placed in a certain position based on its
 * proposed neighbours and their colours/shapes
 * Parameters:
 * tile [Tile*] - The tile they wish to place
 * position [string] - The location the tile wants to be palced at
 * Return:
 * bool - If the placement is valid [true] or not [false]
 */
bool GameState::validateTile(Tile* tile, std::string position) {
  bool valid = true;
  bool hasNeighbour = false;

  // For vertical (0) and horizontal (1) directions
  for (int direction = 0; valid && direction < 2; direction++) {
    // Get all of the connected tiles in both directions
    LinkedList* connectedA = getConnectedTilesInDir(tile, position, direction);
    LinkedList* connectedB = getConnectedTilesInDir(tile, position, direction
                                                                      + 2);

    // Update whether we have a neighbour
    hasNeighbour = hasNeighbour ||
      connectedA->getSize() > 0 ||
      connectedB->getSize() > 0;

    // Validate all of these connected neighbours
    for (int i = 0; valid && i < connectedA->getSize(); i++) {
      if (!checkPlacementValid(tile, connectedA->get(i))) {
        std::cout << "You can't place a " << tile->toString() << " tile here!"
                  << std::endl;
        valid = false;
      }
    }

    // Validate all of these connected neighbours
    for (int i = 0; valid && i < connectedB->getSize(); i++) {
      if (!checkPlacementValid(tile, connectedB->get(i))) {
        std::cout << "You can't place a " << tile->toString() << " tile here!"
                  << std::endl;
        valid = false;
      }
    }

    // Check that both directions validate the same way
    if (connectedA->getSize() > 0 && connectedB->getSize() > 0) {
      if (!checkPlacementValid(connectedA->get(0), connectedB->get(0))) {
        std::cout << "You can't place a " << tile->toString() << " tile here!"
                  << std::endl;
        valid = false;
      }
    }

    delete connectedA;
    delete connectedB;
  }

  if (!hasNeighbour) {
    std::cout << "You can't place a tile here!" << std::endl;
    valid = false;
  }

  return valid;
}

/*
 * Method Name: checkPlacementValid
 * Purpose: Checks if two tiles are valid to be placed next to eachother
 * Parameters:
 * myTile [Tile*] - The tile to be placed
 * neighbourTile [Tile*] - The tile already on board
 * Return:
 * bool - If the placement is valid [true] or not [false]
 */
bool GameState::checkPlacementValid(Tile* myTile, Tile* neighbourTile) {
  bool colourMatch = neighbourTile->getColour() == myTile->getColour();
  bool shapeMatch = neighbourTile->getShape() == myTile->getShape();
  return ((colourMatch) != (shapeMatch));
}
