#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"
#include "GamePlay.h"


GameState::GameState(std::string player1Name, std::string player2Name) {
  players = new Player*[2];
  players[0] = new Player(player1Name);
  players[1] = new Player(player2Name);
  board = new Board(20, 20);
  gamePlay = new GamePlay(board);
  //GamePlay* gamePlay = new GamePlay();
  bag = new TileBag();
  players[0]->initHand(bag);
  players[1]->initHand(bag);
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
  gamePlay = new GamePlay(board);
  //GamePlay* gamePlay = new GamePlay();

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
  Player* player = players[0];
  bool success = false;
  int tileIndex = player->getHand()->getIndexOf(tileString);
  if (tileIndex != TILE_NOT_FOUND) {
    if (board->getTile(position[0], position[1]) == nullptr) {
      Tile* tile = player->getHand()->remove(tileIndex);
      board->addTile(tile, position[0], position.substr(1, position.length()));
      if (bag->getList()->getSize() > 0) {
        player->getHand()->push(bag->draw());
      }
      Tile* playedTile = new Tile(tileString[0], tileString[1]);
      gamePlay->submittedTurn(playedTile, position);

      //new Tile*(tileString[0], tileString[1]), position);
      success = true;
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
  for (int i = 0; i <= 1; i++) {
    ss << players[i]->getName() << "\n" << players[i]->getScore() << "\n" <<
       players[i]->getHand()->toString() << "\n";
  }
  ss << board->getWidth() << "," << board->getHeight() << "\n" <<
  board->toString() << "\n" << bag->getList()->toString() << "\n";
  // TODO Add current player tracker and add to serialise method
  return ss.str();
}
