#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"

class GameState {
  public:
    GameState(Player* players);
    ~GameState();
    void InitialHand(LinkedList* hand);

  private:
    Player* players;
    Board* board;
    TileBag bag;
};

#endif //COSC_ASSIGN_TWO_GS
