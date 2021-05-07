#include <iostream>
#include <vector>
#include <string>
#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"

GameState::GameState(std::string player1Name, std::string player2Name) {
  players[0] = new Player(player1Name);
  players[1] = new Player(player2Name);
  board = new Board(20, 20);
  bag = new TileBag();
  players[0]->initHand(bag);
  players[1]->initHand(bag);
}

GameState::GameState(std::istream stream) {
  // TODO
}

void GameState::doPlaceTile(std::string tile, std::string position) {
  std::cout << "TODO: IMPL PLACE " << tile << " to " << position << "'" << std::endl;
}

Player* GameState::currentPlayer() {
  // TODO: alternate players
  return players[0];
}

void GameState::doReplaceTile(std::string tile) {
  int i = 0;
  bool found = false;
  Player* player = currentPlayer();
  while (!found && player->getHand()->get(i) != nullptr) {
    if (tile == player->getHand()->get(i)->toString()) {
      player->getHand()->remove(i);
      player->getHand()->push(bag->draw());
      bag->getList()->push(player->getHand()->get(i));
      bag->shuffle();
      found = true;  
    }
    i++;
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
  return "";
}

void GameState::initHand(LinkedList* hand) {
    for(int i = 0; i < 6; i++) {
        hand->push(TileBag().draw());
    }
}
