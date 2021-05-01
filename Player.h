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
