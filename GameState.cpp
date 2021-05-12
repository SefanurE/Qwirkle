#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"


GameState::GameState(std::string player1Name, std::string player2Name) {
  players = new Player*[2];
  players[0] = new Player(player1Name);
  players[1] = new Player(player2Name);
  board = new Board(26, 26);
  bag = new TileBag();
  players[0]->initHand(bag);
  players[1]->initHand(bag);
  firstTile = true;
}

GameState::GameState(std::istream &gameData) {
  players = new Player*[PLAYER_COUNT];

  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::string tempPlayerInfoString = "";
    getline(gameData, tempPlayerInfoString);
    players[i] = new Player(tempPlayerInfoString);
    getline(gameData, tempPlayerInfoString);
    players[i]->setScore(stoi(tempPlayerInfoString));
    getline(gameData, tempPlayerInfoString);
    players[i]->getHand()->fromString(tempPlayerInfoString);
  }

  std::string boardShapeString = "";
  getline(gameData, boardShapeString);
  std::string placedTileString = "";
  getline(gameData, placedTileString);

  board = new Board(boardShapeString, placedTileString);

  std::string tileBagString = "";
  getline(gameData, tileBagString);
  bag = new TileBag(tileBagString);

  // TODO: Current players (EWAN)
}

void GameState::showBeforeRoundOutput() {
  std::cout << std::endl << getCurrentPlayer()->getName() << ", it's your turn" << std::endl;
  for (int playerIndex = 0; playerIndex < PLAYER_COUNT; playerIndex++) {
    std::cout << "Score for " << players[playerIndex]->getName() << ": " << players[playerIndex]->getScore() << std::endl;
  }
  board->printBoard();
  std::cout << std::endl << "Your hand is" << std::endl << getCurrentPlayer()->getHand()->toString() << std::endl << std::endl;
  std::cout << "Current score: " << players[0]->getScore() << std::endl;
  std::cout << "BAG CONTAINS " << bag->getList()->toString() << std::endl;
}

bool GameState::doPlaceTile(std::string tileString, std::string position) {
  Player* player = getCurrentPlayer();
  Tile* playedTile = new Tile(tileString[0], tileString[1]);
  bool success = false;
  int tileIndex = player->getHand()->getIndexOf(tileString);
  
  int row = board->rowToInt(position[0]);
  std::string colstr = position.substr(1, position.length());
  int col = std::stoi(colstr);
  
  std::cout << "Checks. Row: " << row << " " << " col: " << col << std::endl;
  if (tileIndex != TILE_NOT_FOUND) {
    if (col >= 0 && row  >= 0 && col < board->getWidth() && row < board->getHeight()) {
      if (board->getTile(row, col) == nullptr) {
        int scoreForRound = validateTile(playedTile, row, col);
        //Checks if either first tile being placed or not first with a valid score
        //-1 is returned if tile placement is invalid
        if (firstTile || (!firstTile && scoreForRound != -1)) {
          //If first tile being placed, sets points to 1
          if(firstTile) {
            player->setScore(1);
          } else {
            //Uses the return of the validation method to update the player points
            player->updateScore(scoreForRound);
          }
          //If placement was successful, the placed tile is removed from the hand
          //and added to the board
          Tile* tile = player->getHand()->remove(tileIndex);
          board->addTile(tile, position[0], position.substr(1, position.length()));

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
      std::cout << "Location selected is out of bounds" << std::endl;
    }
  } else {
    std::cout << "You do not have a " << tileString << " tile!" << std::endl;
  }
  //Next player is called upon a successful end to a round
  if(success) {
    nextPlayer();
  }

  return success;
}

Player* GameState::getCurrentPlayer() {
  // TODO: alternate players
  return players[0];
}

void GameState::nextPlayer() {
  //currentPlayerIndex = (currentPlayerIndex + 1) % PLAYER_COUNT;
}

bool GameState::doReplaceTile(std::string tile) {
  Player* player = getCurrentPlayer();
  LinkedList* hand = player->getHand();
  bool success = false;
  int tileIndex = hand->getIndexOf(tile);
  if (tileIndex != TILE_NOT_FOUND) {
    hand->insertAfter(tileIndex, bag->draw());
    if (bag->getList()->getSize() != 0) {
      bag->getList()->push(hand->remove(tileIndex));
      success = true;
    } else {
      std::cout << "The bag is empty! You cannot replace your tile!" << std::endl;
    }
    // TODO: swap players
  } else {
    std::cout << "You do not have a " << tile << " tile!" << std::endl;
  }
  //switches to next player after tile replacement (turn used)
  if(success) {
    nextPlayer();
  }

  return success;
}

GameState::~GameState(){
  delete players[0];
  delete players[1];
  delete[] players;
  delete board;
  delete bag;
}

std::string GameState::serialise() {
  std::stringstream ss;
  for (int i = 0; i <= 1; i++) {
    ss << players[i]->getName() << "\n" << players[i]->getScore() << "\n" <<
       players[i]->getHand()->toString() << "\n";
  }
  ss << board->getWidth() << "," << board->getHeight() << "\n" <<
  board->toString() << "\n" << bag->getList()->toString() << "\n";
  // TODO Add current player tracker and add to serialise method
  return ss.str();
}

int GameState::validateTile(Tile* tile, int row, int col) {
  //place increment directions into a pair array
  std::pair<int, int> directions[4] = {std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0)};
  int direction = 0;
  int step = 1;
  int calcScore = 0;
  bool hasNeighbour = false;
  bool validated = true;
  int roundScore = 0;

  //loop that iterates through all the neighbours in each direction
  while(validated && direction < 4) {
    std::cout << "In the loop " << std::endl;
    //as steps are incremented, the directions are multiplied by the steps to move
    int nextRow = row + directions[direction].first * step;
    int nextCol = col + directions[direction].second * step;

    //ensures we dont check for neighbours outside of the board limits to prevent segmentation error
    if (nextCol >= 0 && nextRow  >= 0 && nextCol < board->getWidth() && nextRow < board->getHeight()) {
      Tile* neighbourTile = board->getTile(nextRow, nextCol);

      //ensures there is a neighbour to validate against
      if (neighbourTile != nullptr) {
        hasNeighbour = true;

        //exits the loop if the tile is not valid in the chosen location
        if (!checkPlacementValid(tile, neighbourTile)) {
          std::cout << "TILE IS NOT VALID" << std::endl;
          validated = false;
        } else {
          //if the adjacent tile is validate, the subsequent tiles are checked
          step++;

        }
      } else {
          if(step > 1) {
            //score is calculated based on the number of tiles in the line
            calcScore = calcScore + step;
          }

        if (step == QWIRKLE) {
          std::cout << std::endl;
          std::cout << "QWIRKLE!!" << std::endl;
          calcScore = calcScore + step;
        }
        direction++;
        step = 1;
      }
    }
    else {
      direction++;
      step = 1;
    }
  }

  //if there are no neighbours then the placement isnt valid
  //and so if there are no neighbours or the placement isnt valid
  //calcScore will equal -1 (which gets returned and checked)
  if (!hasNeighbour || !validated) {
    roundScore = -1;
  } else {
    roundScore = calcScore;
  }
  return roundScore;
}

bool GameState::checkPlacementValid(Tile* myTile, Tile* neighbourTile) {
    bool check = false;
    //XOR operator to ensure that only either the colour or the shape match
    if((neighbourTile->colour == myTile->colour) ^ (neighbourTile->shape == myTile->shape-48)) {
        check = true;
    }
    return check;
}
