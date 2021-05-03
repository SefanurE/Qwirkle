#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"

class GameState{
  public:

    GameState(Player* players);
    ~GameState();
    void InitialHand(LinkedList* hand);

  private:

};

#endif //COSC_ASSIGN_TWO_GS
