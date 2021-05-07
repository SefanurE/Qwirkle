#include "Player.h"

Player::Player(std::string name) {
  this->name = name;
  hand = new LinkedList();
  score = 0;
}

std::string Player::getName() {
  return name;
}

LinkedList* Player::getHand() {
  return hand;
}

int Player::getScore() {
  return score;
}

void Player::setScore(int score) {
  this->score = score;
}

void Player::initHand(TileBag* bag) {
    for(int i = 0; i < HANDSIZE; i++) {
        hand->push(bag->draw());
    }
}
