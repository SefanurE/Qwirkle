#include "Player.h"

Player::Player(std::string name) {
  this->name = name;
  hand = new LinkedList();
}

std::string Player::getName() {
  return name;
}

LinkedList* Player::getHand() {
  return hand;
}