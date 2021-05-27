#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"

#define TILE_NOT_FOUND -1
#define QWIRKLE 6
#define BOARD_SIZE 26
#define NO_TILE_COL -1
#define NO_TILE_ROW ' '

class GameState {
  public:
    Board* board;

    GameState(std::vector<std::string> playerNames, bool multiPlace, bool coloured);
    GameState(std::istream &stream, int numPlayers, bool multiPlace, bool coloured);
    ~GameState();
    std::string serialise();
    Player* getWinningPlayer();
    bool isGameOver();
    bool doPlaceTile(std::string tileString, std::string position);
    bool doReplaceTile(std::string tile);
    bool doEndTurn();
    void showBeforeRoundOutput();
    void showAfterGameOutput();
    bool testSaveFileValidity(std::istream &gameData);

  private:
    Tile* firstTile;
    int currentPlayerIndex;
    Player** players;
    TileBag* bag;
    int numPlayers;
    bool multiPlace;
    bool coloured;

    char firstTileRow = NO_TILE_ROW;
    int firstTileCol = NO_TILE_COL;

    char validTileRowCreated = NO_TILE_ROW;
    int validTileColCreated = NO_TILE_COL;

    int placedTilesOnTurn = 0;
    bool newGame;

    Player* getCurrentPlayer();
    LinkedList* getConnectedTilesInDir(std::string position, int dir);
    bool validateTile(Tile* tile, std::string position);
    int placeTileScore(Tile* tile, std::string position);
    bool checkPlacementValid(Tile* myTile, Tile* neighbourTile);
    void nextPlayer();
};

#endif //COSC_ASSIGN_TWO_GS
