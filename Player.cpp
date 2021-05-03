#include "Player.h"

Player::Player() {
}

Player::Player(std::string name) {
  this->name = name;
  hand = new LinkedList();
  initHand();

}

std::string Player::getName() {
  return name;
}

LinkedList* Player::getHand() {
  return hand;
}

void Player::initHand() {
    for(int i = 0; i < HANDSIZE; i++) {
        hand->push(TileBag().draw());
    }
}