#include <iostream>
#include <vector>
#include <string>
#include "GameState.h"

GameState::GameState(Player currentPlayer, Board board, TileBag tileBag) {
  player = currentPlayer;
  this->board = board;
  this->tileBag = tileBag;

}

GameState::GameState(std::istream stream) {
  // TODO
}

GameState::~GameState(){
  //delete players[0];
  //delete players[1];
  //delete[] players;
  //delete board;
  //delete tileBag;
}

std::string GameState::serialise() {
  return "";
}

void GameState::doPlaceTile(std::string tile, std::string position) {

  std::cout << "TODO: IMPL PLACE " << tile << " to " << position << "'" << std::endl;
}

void GameState::doReplaceTile(std::string tile) {
  int i = 0;
  while(!found && player.getHand()->get(i) != nullptr) {
    if(tile == player.getHand()->get(i)->toString()) {
      player.getHand()->remove(i);
      player.getHand()->push(tileBag.draw());
      tileBag.getList()->push(player.getHand()->get(i));
      tileBag.shuffle();

      found = true;  
    }
    ++i;
  }

  //std::cout << "Tile object to be replaced: " << player->getHand()->get(i) << std::endl;
  std::cout << "TODO: IMPL REPLACE " << tile << std::endl;
}
