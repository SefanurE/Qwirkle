#include "LinkedList.h"

class Player {
private:
  std::string name;
  LinkedList hand;
public:
  std::string getName();
  LinkedList getHand();
};
