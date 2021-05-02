#include "Player.h"

Player::Player(std::string name) {
  this->name = name;
  hand = new LinkedList();
}

LinkedList Player::getHand() {
  return hand;
}