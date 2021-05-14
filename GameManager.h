#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "GameState.h"
#include "Board.h"

#define PROMPT "> "
#define COMM_QUIT "QUIT"
#define COMM_SAVE "SAVE"
#define COMM_PLACE "PLACE"
#define COMM_REPLACE "REPLACE"
#define COMM_AT "AT"
#define COMM_TILE "[A-Z][0-9]+"

enum GameManagerState {
  DEFAULT,
  PLAYING,
  QUIT
};

class GameManager {

  private:
    void parseCommand(std::string command);
    void doQuit();
    void doSave(std::string path);
    void doPlaceTile(std::string tile, std::string position);
    void doReplaceTile(std::string tile);
    GameState* gameState;
    GameManagerState status = DEFAULT;
    bool showRoundOutput = true;
    bool imatch(std::string s, std::string pattern);

  public:
    GameManager(); ~GameManager();
    void startGame();
    void newGame(std::string playerNames[PLAYER_COUNT]);
    void loadGame(std::string fileName);
};
