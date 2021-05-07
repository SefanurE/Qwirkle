#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER
#include "LinkedList.h"
#include "TileBag.h"

#define HANDSIZE 6



class Player {
private:
  std::string name;
  LinkedList* hand;
public:
  Player();
  Player(std::string name);
  std::string getName();
  LinkedList* getHand();
  void initHand(TileBag* bag);

};

#endif //COSC_ASSIGN_TWO_PLAYER
