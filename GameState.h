#ifndef COSC_ASSIGN_TWO_GS
#define COSC_ASSIGN_TWO_GS

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"

#define PROMPT           "> "
#define TWO_PLAYER_COUNT 2
#define TILE_NOT_FOUND   -1
#define QWIRKLE          6
#define BOARD_SIZE       26
#define NEW_FORMAT       "enhanced"
#define AI_START_POS     "M12"

#define NAME_PATTERN "(^[A-Z]+$)|(^\\[AI\\] [A-Z]+$)"
#define SCORE_PATTERN "^\\d+$"
#define HAND_PATTERN "^(([A-Z][0-9]+),)*([A-Z][0-9]+)$|(^$)"
#define BOARD_SIZE_PATTERN "^\\d+,\\d+$"
#define BOARD_TILES_PATTERN "^(([A-Z][0-9]+)@([A-Z][0-9]+),\\s?)*\
([A-Z][0-9]+)@([A-Z][0-9]+)$|(^$)"
#define BAG_TILES_PATTERN "^(([A-Z][0-9]+),)*([A-Z][0-9]+)$|(^$)"

class GameState {
  public:
    Board* board;

    GameState(std::string playerNames[], int playerCount);
    GameState(std::istream &stream);
    ~GameState();
    std::string serialise();
    Player* getWinningPlayer();
    bool isGameOver();
    bool doPlaceTile(std::string tileString, std::string position);
    bool doReplaceTile(std::string tile);
    void showBeforeRoundOutput(bool coloured);
    void showAfterGameOutput(bool coloured);
    bool testSaveFileValidity(std::istream &gameData);
    Player* getCurrentPlayer();
    void determineAIMove();

  private:
    int playerCount;
    bool firstTile;
    int currentPlayerIndex;
    Player** players;
    TileBag* bag;
   
    void nextPlayer();
    LinkedList* getConnectedTilesInDir(std::string position, int dir);
    bool validateTile(Tile* tile, std::string position);
    int placeTileScore(Tile* tile, std::string position);
    bool checkPlacementValid(Tile* myTile, Tile* neighbourTile);
    void makeAIMove(Tile* tile, std::string position);
    bool hasNeighbour(std::string position);
    std::string intToStringPosition(int row, int col);
};

#endif //COSC_ASSIGN_TWO_GS
