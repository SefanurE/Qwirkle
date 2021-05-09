#ifndef COSC_ASSIGN_TWO_GAMEPLAY
#define COSC_ASSIGN_TWO_GAMEPLAY
#include <iostream>
#include <vector>
#include <string>
#include "Tile.h"
#include "Board.h"
#include "GameState.h"


class GamePlay {
public:
    GamePlay(Board* board);
    ~GamePlay();
    bool submittedTurn(Tile* tile, std::string position);


private:
    bool checkAdjacent(Tile* tile, std::string position);
    bool checkPlacementValid(Tile* myTile, Tile* neighbourTile);

    bool outSuccess = false;
    Board* board = new Board();
};

#endif //COSC_ASSIGN_TWO_GAMEPLAY
