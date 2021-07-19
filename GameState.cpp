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
 * playerCount [int] - Number of players
 * Return: N/A
 */
GameState::GameState(std::string playerNames[], int playerCount) {
  this->playerCount = playerCount;
  players = new Player* [playerCount];
  board = new Board(BOARD_SIZE, BOARD_SIZE);
  bag = new TileBag();
  bool isAI = false;
  for (int i = 0; i < playerCount; i++) {
    std::string startOfName = playerNames[i].substr(0, 3);
    if (startOfName == "AI ") {
      playerNames[i] = "[AI] " + playerNames[i].substr(3);
      isAI = true;
    }
    players[i] = new Player(playerNames[i], isAI);
    players[i]->initHand(bag);
    // Reset value
    isAI = false;
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
  for (int i = 0; i < playerCount; i++) {
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
GameState::GameState(std::istream& gameData) {
  std::string firstLine = "";
  getline(gameData, firstLine);

  // Check if new save format
  if (firstLine == NEW_FORMAT) {
    // Read player count
    std::string playerCountStr = "";
    getline(gameData, playerCountStr);
    playerCount = stoi(playerCountStr);
  } else {
    // Set playerCount to original count of 2
    playerCount = TWO_PLAYER_COUNT;
  }
  // Read player information
  players = new Player* [playerCount];
  bool isAI = false;
  for (int i = 0; i < playerCount; i++) {
    std::string tempPlayerInfoString = "";
    std::string startOfName = "";

    // If first player and file is original save format, use the firstLine
    // string which already has the player name to construct player
    if (i == 0 && firstLine != NEW_FORMAT) {
      startOfName = firstLine.substr(0, 5);
      if (startOfName == "[AI] ") {
        isAI = true;
      }
      players[i] = new Player(firstLine, isAI);
    } else {
      // Read the player name and construct the player
      getline(gameData, tempPlayerInfoString);
      startOfName = tempPlayerInfoString.substr(0, 5);
      if (startOfName == "[AI] ") {
        isAI = true;
      }
      players[i] = new Player(tempPlayerInfoString, isAI);
    }
    // Resets value
      isAI = false;
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
  for (int i = 0; i < playerCount; i++) {
    if (players[i]->getName() == currentPlayerName) {
      currentPlayerIndex = i;
    }
  }
  
}

/*
 * Constructor Name: testSaveFileValidity
 * Purpose: Confirm that gameData matches a valid save format utalising REGEX
 * Parameters:
 * gameData [istream] - A reference to the gameData istream
 */
bool GameState::testSaveFileValidity(std::istream& gameData) {
  int playerCount = 0;
  std::string firstLine = "";
  getline(gameData, firstLine);
  // Check if new save format
  if (firstLine == NEW_FORMAT) {
    std::string playerCountStr = "";
    getline(gameData, playerCountStr);
    // Set playerCount
    playerCount = stoi(playerCountStr);
  } else {
    playerCount = TWO_PLAYER_COUNT;
  }

  // Create array of patterns
  std::string patterns[playerCount * 3 + 4] = {};

  // Add player patterns
  for (int i = 0; i < playerCount; i++) {
    patterns[i * 3] = NAME_PATTERN;
    patterns[i * 3 + 1] = SCORE_PATTERN;
    patterns[i * 3 + 2] = HAND_PATTERN;
  }

  // Add game patterns
  patterns[playerCount * 3 + 0] = BOARD_SIZE_PATTERN;
  patterns[playerCount * 3 + 1] = BOARD_TILES_PATTERN;
  patterns[playerCount * 3 + 2] = BAG_TILES_PATTERN;
  patterns[playerCount * 3 + 3] = NAME_PATTERN;

  // Check the file against all the patterns, line by line
  bool valid = true;
  std::string line = "";
  for (int i = 0; i < playerCount * 3 + 4; i++) {
    // If file is original save format, check firstLine's pattern
    if (i == 0 && firstLine != NEW_FORMAT) {
      valid = std::regex_match(firstLine, std::regex(patterns[i]));
    } else {
      getline(gameData, line);
      valid = valid && std::regex_match(line, std::regex(patterns[i]));
    }
  }
  return valid;
}

/*
 * Method Name: isGameOver()
 * Purpose: Determine whether the game is over.
 */
bool GameState::isGameOver() {
  // Is the game over?
  bool gameOver = false;
  if (bag->getList()->getSize() == 0) {
    for (int i = 0; !gameOver && i < playerCount; i++) {
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
 * Parameters: N/A
 * Return: Pointer to player with highest score, nullptr if draw
 */
Player* GameState::getWinningPlayer() {
  Player* winner = nullptr;

  // Is the game over?
  if (isGameOver()) {
    // Get player w/ highest score (if there is one)
    bool isDraw = false;
    winner = players[0];
    for (int i = 1; !isDraw && i < playerCount; i++) {
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
 * Parameters: 
 * coloured [bool] - Whether the player toggled colours on [true] or not [false]
 * Return: void
 */
void GameState::showAfterGameOutput(bool coloured) {
  std::cout << std::endl;
  std::cout << "Game over" << std::endl << std::endl;
  std::cout << "Final board" << std::endl;
  board->printBoard(coloured);
  for (int i = 0; i < playerCount; i++) {
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
 * Parameters:
 * coloured [bool] - Whether the player toggled colours on [true] or not [false]
 * Return: void
 */
void GameState::showBeforeRoundOutput(bool coloured) {
  // Display the current players name
  std::cout << std::endl
            << getCurrentPlayer()->getName() << ", it's your turn" << std::endl;

  // Display all players score
  for (int playerIndex = 0; playerIndex < playerCount; playerIndex++) {
    std::cout << "Score for " << players[playerIndex]->getName() << ": "
              << players[playerIndex]->getScore() << std::endl;
  }

  // Display the board
  board->printBoard(coloured);

  // Display the current players hand
  std::cout << std::endl
            << "Your hand is" << std::endl;
  if (!coloured) {
    std::cout << getCurrentPlayer()->getHand()->toString()
              << std::endl;
  } else {
    std::cout << getCurrentPlayer()->getHand()->toStringColour()
              << std::endl;
  }
  
}

/*
 * Method Name: doPlaceTile
 * Purpose: Validates both the desired location and tile the user wants to place
 * If valid, moves the tile from the players hand to the board and updates
 * score. Otherwise notifies player of invalid move.
 * Parameters:
 * tileString [string] - Tile the player wants to place on the board
 * position [string] - Desired position in which to place the tile
 * Return: 
 * bool - If the tile was successfully placed [true] or not [false]
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
        if (firstTile || getCurrentPlayer()->getIsAI() || validateTile(playedTile, position)) {
          // Remove the tile from the players hand and place it on the board
          Tile* tile = player->getHand()->remove(tileIndex);
          board->addTile(tile, row, col);

          // Award score for this move
          // First tile gets 1 point
          int score = placeTileScore(playedTile, position) 
                                     + (firstTile ? 1 : 0);
          player->addScore(score);

          while (score >= QWIRKLE*2) {
            std::cout << std::endl << "QWIRKLE!!!" << std::endl;
            score = score - QWIRKLE*2;
          }

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
  currentPlayerIndex = (currentPlayerIndex + 1) % playerCount;
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
  // Get the player and their hand
  Player* player = getCurrentPlayer();
  LinkedList* hand = player->getHand();

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

/*
 * Method Name: serialise
 * Purpose: Converts all game data into a string stream to be saved to a file
 * Parameters: N/A
 * Return:
 * string - All important gamedata in the correct save format
 */
std::string GameState::serialise() {
  std::stringstream ss;

  // Write enhanced so when loading, program knows it is new format
  ss << "enhanced" << std::endl;

  // Write player count
  ss << playerCount << std::endl;

  // Write player info
  for (int i = 0; i < playerCount; i++) {
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

/*
 * Method Name: getConnectedTilesInDir
 * Purpose: Get tiles connected to (tile) in specified direction (dir) in
 * ascending distance order.
 * Parameters:
 * tile [Tile*] - The tile they wish to place 
 * position [string] - The location the tile wants to be placed at
 * dir [int] - Direction the methods checking, 0=down, 1=left, 2=up, 3=right
 * Return:
 * LinkedList* - list of tiles in specified direction
 */
LinkedList* GameState::getConnectedTilesInDir(std::string position,
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
 * tile [Tile*] - The tile they wish to place
 * position [string] - The location the tile wants to be placed at
 * Return:
 * int - Additional score that tile place gives
 */
int GameState::placeTileScore(Tile* tile, std::string position) {
  int roundScore = 0;
  bool gotRowScore = false;
  bool gotColScore = false;

  // For each orthogonal direction (UP, LEFT, DOWN, RIGHT)
  for (int direction = 0; direction < 4; direction++) {
    // Award points for the length of the amount of connected tiles in this 
    // direction
    LinkedList* connected = getConnectedTilesInDir(position, direction);
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

    // Award double points if the length is a QWIRKLE!!!
    if (connected->getSize() == QWIRKLE - 1) {
      roundScore += QWIRKLE;
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
 * position [string] - The location the tile wants to be placed at
 * Return:
 * bool - If the placement is valid [true] or not [false]
 */
bool GameState::validateTile(Tile* tile, std::string position) {
  bool valid = true;
  bool hasNeighbour = false;

  // For vertical (0) and horizontal (1) directions
  for (int direction = 0; valid && direction < 2; direction++) {
    // Get all of the connected tiles in both directions
    LinkedList* connectedA = getConnectedTilesInDir(position, direction);
    LinkedList* connectedB = getConnectedTilesInDir(position, direction + 2);

    // Update whether we have a neighbour
    hasNeighbour = hasNeighbour ||
      connectedA->getSize() > 0 ||
      connectedB->getSize() > 0;

    // Validate all of these connected neighbours
    for (int i = 0; valid && i < connectedA->getSize(); i++) {
      if (!checkPlacementValid(tile, connectedA->get(i))) {
        valid = false;
      }
    }

    // Validate all of these connected neighbours
    for (int i = 0; valid && i < connectedB->getSize(); i++) {
      if (!checkPlacementValid(tile, connectedB->get(i))) {
        valid = false;
      }
    }

    // Check that both directions validate the same way
    if (connectedA->getSize() > 0 && connectedB->getSize() > 0) {
      if (!checkPlacementValid(connectedA->get(0), connectedB->get(0))) {
        valid = false;
      }
    }

    if (!valid && !getCurrentPlayer()->getIsAI()) {
      std::cout << "You can't place a " << tile->toString() << " tile there!"
                  << std::endl;
    }

    delete connectedA;
    delete connectedB;
  }

  if (!hasNeighbour) {
    if (!getCurrentPlayer()->getIsAI()) {
      std::cout << "You can't place a tile here!" << std::endl;
    }
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

/*
 * Method Name: determineAIMove
 * Purpose: Checks all board positions then determines where to place if there
 * are any valid moves
 * Parameters: N/A
 * Return: N/A
 */
void GameState::determineAIMove() {
  Player* player = getCurrentPlayer();
  LinkedList* hand = player->getHand();

  // If AI needs to make first move, place first tile in hand at M12
  if (firstTile) {
    Tile* tile = hand->get(0);
    std::string tileStr = tile->toString();
    doPlaceTile(tileStr, AI_START_POS);
  // If not the first move of the game
  } else {
    bool valid = false;
    int score = 0;
    int maxScore = 0;
    Tile* maxTile = nullptr;
    std::string maxPosition = "";

    // Loop through all positions on the board
    for (int x = 0; x < board->getHeight(); x++) {
      for (int y = 0; y < board->getWidth(); y++) {
        Tile* position = board->getTile(x, y);
        std::string positionStr = intToStringPosition(x, y);

        // Check if position isn't taken by a tile and has a neighbour
        if (position == nullptr && hasNeighbour(positionStr)) {
          // Loop through tiles in AI's hand
          for (int handIndex = 0; handIndex < hand->getSize(); ++handIndex) {
            Tile* tile = hand->get(handIndex);
            // Check if place is valid
            valid = validateTile(tile, positionStr);
            if (valid) {
              score = placeTileScore(tile, positionStr);
              // Check if current score is greater than maxScore, hence meaning
              // it is better move
              if (score > maxScore) {
                // Keep track of new better place move
                maxScore = score;
                maxTile = tile;
                maxPosition = positionStr;
              }
            }
          }
        }
      }
    }
    // Make the move based off of what was found
    makeAIMove(maxTile, maxPosition);
  }
}

/*
 * Method Name: makeAIMove
 * Purpose: Makes the AI's move and prints out the respective command
 * Parameters:
 * tile [Tile*] - Tile the AI wants placed
 * position [string] - Location tile will be placed
 * Return: N/A
 */
void GameState::makeAIMove(Tile* tile, std::string position) {
  Player* player = getCurrentPlayer();
  LinkedList* hand = player->getHand();
  // If there was a maxTile, simulate command input by outputting it and
  // place maxTile in maxPosition
  std::cout << PROMPT;
  if (tile != nullptr) {
    std::string tileStr = tile->toString();
    std::cout << "Place " << tileStr << " at " << position;
    std::cout << std::endl;
    doPlaceTile(tileStr, position);
  // If there was no maxTile, replace first tile in AI's hand
  } else {
    std::string firstHandTile = hand->get(0)->toString();
    std::cout << "Replace " << firstHandTile;
    std::cout << std::endl;
    doReplaceTile(firstHandTile);
  }
}


/*
 * Method Name: hasNeighbour
 * Purpose: Checks if provided position has atleast one neighbour
 * Parameters:
 * position [string] - Position on the board
 * Return:
 * bool - If the position has neighbour [true] or not [false]
 */
bool GameState::hasNeighbour(std::string position) {
  bool hasNeighbour = false;

  // Get row and col from position string
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);

  // Make a set of orthogonal directions
  std::pair<int, int> directions[4] = {
    std::make_pair(0, -1), std::make_pair(-1, 0),
    std::make_pair(0, 1),  std::make_pair(1, 0) };

  for (int dir = 0; !hasNeighbour && dir < 4; ++dir) {
    std::pair<int, int> direction = directions[dir];
    // Determine scan position
    int sRow = row + direction.first;
    int sCol = col + direction.second;

    // Are we are still on the board
    if (board->containsPosition(sRow, sCol)) {
      // Get the tile from this position
      if (board->getTile(sRow, sCol) != nullptr) {
        hasNeighbour = true;
      }
    }
  }
  return hasNeighbour;
}

/*
 * Method Name: intToStringPosition
 * Purpose: Returns the location on the board of the provided row and col
 * Parameters:
 * row [int] - Integer representatin of row location
 * col [int] - Integer representatin of col location
 * Return:
 * string - String representation of position
 */
std::string GameState::intToStringPosition(int row, int col) {
  return board->intToRow(row) + std::to_string(col);
}