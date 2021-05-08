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
  board = new Board(20, 20);
  bag = new TileBag();
  players[0]->initHand(bag);
  players[1]->initHand(bag);
}

GameState::GameState(std::istream &gameData) {
  players = new Player*[2];

  std::string player1Name = "";
  getline(gameData, player1Name);
  players[0] = new Player(player1Name);
  std::cout << players[0]->getName() << std::endl;

  std::string player1Score = "";
  getline(gameData, player1Score);
  players[0]->setScore(stoi(player1Score));
  std::cout << players[0]->getScore() << std::endl;

  std::string player1Hand = "";
  getline(gameData, player1Hand);
  players[0]->getHand()->fromString(player1Hand);
  std::cout << players[0]->getHand()->toString() << std::endl;

  std::string player2Name = "";
  getline(gameData, player2Name);
  players[1] = new Player(player2Name);
  std::cout << players[1]->getName() << std::endl;

  std::string player2Score = "";
  getline(gameData, player2Score);
  players[1]->setScore(stoi(player2Score));
  std::cout << players[1]->getScore() << std::endl;

  std::string player2Hand = "";
  getline(gameData, player2Hand);
  players[1]->getHand()->fromString(player2Hand);
  std::cout << players[1]->getHand()->toString() << std::endl;

  std::string boardShapeString = "";
  getline(gameData, boardShapeString);

  int charIndex = 0;
  std::string width = "";
  std::string height = "";
  std::string block = "";
  while (boardShapeString[charIndex] != '\0') {
    if (boardShapeString[charIndex] != ',') {
      block += boardShapeString[charIndex];
    } else {
      width = block;
      block = "";
    }
    charIndex++;
  }
  height = block;
  board = new Board(stoi(width), stoi(height));
  std::cout << width << "," << height << std::endl;

  // TODO Read placed tiles
  std::string placedTileString = "";
  getline(gameData, placedTileString);
  board->fromString(placedTileString);
  std::cout << board->toString() << std::endl;

  // TODO Read tile locations
  std::string tileLocationsString = "";
  getline(gameData, tileLocationsString);

  std::string tileBagString = "";
  getline(gameData, tileBagString);

  charIndex = 0;
  block = "";
  while (tileBagString[charIndex] != '\0') {
    if (tileBagString[charIndex] != ',') {
      block += tileBagString[charIndex];
    } else {
      Tile* newTile = new Tile(block[0], block[1]);
      bag->getList()->push(newTile);
      block = "";
    }
  }
  Tile* newTile = new Tile(block[0], block[1]);
  bag->getList()->push(newTile);

  std::string currentPlayer = "";
  getline(gameData, currentPlayer);
}

void GameState::showBeforeRoundOutput() {
  std::cout << getCurrentPlayer()->getName() << ", it's your turn" << std::endl;
  for (int playerIndex = 0; playerIndex < PLAYER_COUNT; playerIndex++) {
    std::cout << "Score for " << players[playerIndex]->getName() << ": " << players[playerIndex]->getScore() << std::endl;
  }
  board->printBoard();
  std::cout << std::endl << "Your hand is" << std::endl << getCurrentPlayer()->getHand()->toString() << std::endl << std::endl;
}

void GameState::doPlaceTile(std::string tile, std::string position) {
  std::cout << "TODO: IMPL PLACE " << tile << " to " << position << "'" << std::endl;
}

Player* GameState::getCurrentPlayer() {
  // TODO: alternate players
  return players[0];
}

void GameState::doReplaceTile(std::string tile) {
  Player* player = getCurrentPlayer();
  LinkedList* hand = player->getHand();
  bool found = false;
  for (int i = 0; !found && i < hand->getSize(); i++) {
    if (tile == hand->get(i)->toString()) {
      hand->push(bag->draw());
      bag->getList()->push(hand->remove(i));
      bag->shuffle();
      found = true;
    }
  }
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

void GameState::initHand(LinkedList* hand) {
    for(int i = 0; i < 6; i++) {
        hand->push(TileBag().draw());
    }
}
