#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER
#include "LinkedList.h"

class Player {
private:
  std::string name;
  LinkedList* hand;
public:
  Player(std::string name);
  std::string getName();
  LinkedList* getHand();
};

#endif //COSC_ASSIGN_TWO_PLAYER