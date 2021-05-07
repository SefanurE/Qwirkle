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

void Player::initHand(TileBag* bag) {
    for(int i = 0; i < HANDSIZE; i++) {
        hand->push(bag->draw());
    }
}
