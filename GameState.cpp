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
}

GameState::GameState(std::istream stream) {
  // TODO
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
