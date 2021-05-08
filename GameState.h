#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"

#define PLAYER_COUNT 2

class GameState {
  public:
    GameState(std::string player1Name, std::string player2Name);
    GameState(std::istream &stream);
    ~GameState();
    std::string serialise();
    void doPlaceTile(std::string tile, std::string pos);
    void doReplaceTile(std::string tile);
    void showBeforeRoundOutput();

  private:
    void initHand(LinkedList* hand);
    Player* getCurrentPlayer();
    Player** players;
    Board* board;
    TileBag* bag;
};

#endif //COSC_ASSIGN_TWO_GS
