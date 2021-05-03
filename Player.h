#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER
#include "LinkedList.h"

class Player {
private:
  std::string name;
  LinkedList* hand;
  int score;
public:
  Player(std::string name);
  std::string getName();
  LinkedList* getHand();
  void addHand(Tile* tile);
  void setScore(int score);
  int getScore();
};

#endif //COSC_ASSIGN_TWO_PLAYER