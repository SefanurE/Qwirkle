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
    GameState(std::string playerNames[PLAYER_COUNT]);
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
    Player** players;
    TileBag* bag;
    bool validateTile(Tile* tile, std::string position);
    bool checkPlacementValid(Tile* myTile, Tile* neighbourTile);
    bool firstTile;
    int maxLength;

};

#endif //COSC_ASSIGN_TWO_GS
