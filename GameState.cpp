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

GameState::GameState(std::istream &gameData) {

  std::string player1Name = "";
  getline(gameData, player1Name);
  players[0] = new Player(player1Name);

  std::string player1Score = "";
  getline(gameData, player1Score);
  players[0]->setScore(stoi(player1Score));

  std::string player1Hand = "";
  getline(gameData, player1Hand);
  players[0]->getHand()->fromString(player1Hand);

  std::string player2Name = "";
  getline(gameData, player2Name);
  players[1] = new Player(player2Name);

  std::string player2Score = "";
  getline(gameData, player2Score);
  players[1]->setScore(stoi(player2Score));

  std::string player2Hand = "";
  getline(gameData, player2Hand);
  players[1]->getHand()->fromString(player2Hand);


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
