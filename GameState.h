#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"


#define PLAYER_COUNT 2
#define TILE_NOT_FOUND -1
#define QWIRKLE 6



class GameState {
  public:
    GameState(std::string player1Name, std::string player2Name);
    GameState(std::istream &stream);
    ~GameState();
    std::string serialise();
    bool doPlaceTile(std::string tileString, std::string position);
    bool doReplaceTile(std::string tile);
    void showBeforeRoundOutput();
    Board* board;
    //GamePlay* gamePlay;


  private:
    Player* getCurrentPlayer();
    void nextPlayer();
    Player** players;
    TileBag* bag;
    int validateTile(Tile* tile, int row, int col);
    bool checkPlacementValid(Tile* myTile, Tile* neighbourTile);
    bool firstTile;

};

#endif //COSC_ASSIGN_TWO_GS
