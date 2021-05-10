#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"

GameState::GameState(std::string playerNames[PLAYER_COUNT]) {
  players = new Player*[PLAYER_COUNT];
  board = new Board(20, 20);
  bag = new TileBag();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players[i] = new Player(playerNames[i]);
    players[i]->initHand(bag);
  }
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
  std::cout << "BAG CONTAINS " << bag->getList()->toString() << std::endl;
}

bool GameState::doPlaceTile(std::string tileString, std::string position) {
  // Player* player = getCurrentPlayer();
  Tile* playedTile = new Tile(tileString[0], tileString[1]);
  Player* player = players[0];
  bool success = false;
  int tileIndex = player->getHand()->getIndexOf(tileString);
  std::cout << "right before the ifs" << std::endl;

  if (tileIndex != TILE_NOT_FOUND) {
    std::cout << "inside if tile index not found etc" << std::endl;
    if (board->getTile(position[0], position[1]) == nullptr) {

      if (firstTile || (!firstTile && validate(playedTile, position))) {
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
    std::cout << "You do not have a " << tileString << " tile!" << std::endl;
  }
  return success;
}

Player* GameState::getCurrentPlayer() {
  // TODO: alternate players
  return players[0];
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
  for (int i = 0; i < PLAYER_COUNT; i++) {
    ss << players[i]->getName() << "\n" << players[i]->getScore() << "\n" <<
       players[i]->getHand()->toString() << "\n";
  }
  ss << board->getWidth() << "," << board->getHeight() << "\n" <<
  board->toString() << "\n" << bag->getList()->toString() << "\n";
  // TODO Add current player tracker and add to serialise method
  return ss.str();
}

bool GameState::validate(Tile* tile, std::string position) {
    bool valid = false;
    std::cout << "valid before validate: " << valid << std::endl;
    if(checkAdjacent(tile, position)) {
        valid = true;
    }
  std::cout << "valid after validate: " << valid << std::endl;
    return valid;
}

bool GameState::checkAdjacent(Tile* tile, std::string position) {
    int row = board->rowToInt(position[0]);
    std::string colstr = position.substr(1, position.length());
    int col = std::stoi(colstr);
    std::cout << "position " << " row " << row << " col " << col << std::endl;

    std::pair<int, int> neighbours[4] = {std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0)};
    int i = 0;
    int j = 1;
    bool flag = true;
    bool hasNeighbour = false;
    bool validated = true;
    while(validated && i < 4) {
      int neebRow = row + neighbours[i].first*j;
      int neebCol = col + neighbours[i].second*j;
        //std::cout << "In neighbour loop " << i << " row " << neighbours[i].first << " col " << neighbours[i].second << std::endl;
        if (neebCol >= 0 && neebRow  >= 0 && neebCol < board->getWidth() && neebRow < board->getHeight()) {
          //std::cout << "Inside board at row " << row << " col " << col << std::endl;
            Tile* neighbourTile = board->getTile(neebRow, neebCol);

            if (neighbourTile != nullptr) {
              hasNeighbour = true;
                if (!checkPlacementValid(tile, neighbourTile)) {
                  std::cout << "TILE IS NOT VALID" << std::endl;
                  validated = false;
                } else {
                  j++;
                }
            } else {
              i++;
              j = 1;
            }
        }
    }
    if (!hasNeighbour || !validated) {
      flag = false;
    }
    return flag;
}

bool GameState::checkPlacementValid(Tile* myTile, Tile* neighbourTile) {
    bool check = false;
    
    std::cout << "neighbour tile: " << neighbourTile->colour<< neighbourTile->shape<<std::endl;

    if(neighbourTile->colour == myTile->colour ^ neighbourTile->shape == myTile->shape-48) {
        check = true;
    }
    std::cout << "check: " << check << std::endl;
    return check;
}
