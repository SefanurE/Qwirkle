#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"
#include "LinkedList.h"

class GameState {
  public:
    GameState(Player currentPlayer, Board board, TileBag tileBag);
    GameState(std::istream stream);
    ~GameState();
    std::string serialise();
    void doPlaceTile(std::string tile, std::string position);
    void doReplaceTile(std::string tile);

  private:
    Player player;
    Board board;
    TileBag tileBag;
    bool found = false;

};

#endif //COSC_ASSIGN_TWO_GS
