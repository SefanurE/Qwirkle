#include "Player.h"

/*
 * Constructor Name: Player
 * Purpose: Constructs a player with given name
 * Parameters:
 * name [string] - Name of player
 * Return: N/A
 */
Player::Player(std::string name, bool isAI) {
  this->name = name;
  hand = new LinkedList();
  score = 0;
  this->isAI = isAI;
}

/*
 * Deconstuctor Name: Player
 * Purpose: Deletes nodes within the hand of the player
 * Parameters: N/A
 * Return: N/A
 */
Player::~Player() {
  delete hand;
}

/*
 * Method Name: getName
 * Purpose: Retrieves the name of the player
 * Parameters: N/A
 * Return:
 * string - Name of the player
 */
std::string Player::getName() {
  return name;
}

/*
 * Method Name: getHand
 * Purpose: Retrieves the hand of the player
 * Parameters: N/A
 * Return:
 * LinkedList* - Hand of the player
 */
LinkedList* Player::getHand() {
  return hand;
}

/*
 * Method Name: getScore
 * Purpose: Retrieves the score of the player
 * Parameters: N/A
 * Return:
 * int - Score of the player
 */
int Player::getScore() {
  return score;
}

/*
 * Method Name: setScore
 * Purpose: Sets the score of the player
 * Parameters:
 * score [int] - The new value of score
 * Return: N/A
 */
void Player::setScore(int score) {
  this->score = score;
}

/*
 * Method Name: addScore
 * Purpose: Adds to the score of the player
 * Parameters:
 * newScore [int] - Value to increase player score by
 * Return: N/A
 */
void Player::addScore(int newScore) {
  score += newScore;
}

/*
 * Method Name: initHand
 * Purpose: Provides player with inital hand of tiles from bag
 * Parameters:
 * bag [TileBag*] - The bag to draw tiles from
 * Return: N/A
 */
void Player::initHand(TileBag* bag) {
  for (int i = 0; i < HANDSIZE; i++) {
    hand->push(bag->draw());
  }
}

/*
 * Method Name: getIsAI
 * Purpose: Retrieves player's AI status
 * Parameters: N/A
 * Return: bool - [true] if the player is an AI otherwise [false]
 */
bool Player::getIsAI() {
  return isAI;
}