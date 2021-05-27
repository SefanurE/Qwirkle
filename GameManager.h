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
#define COMM_DONE "DONE"
#define COMM_AT "AT"
#define COMM_TILE "[A-Z][0-9]+"
#define PATH_PATTERN "((?:[^/\\s]*\\/)*)([^/\\s]+)"
#define COMM_TILE "[A-Z][0-9]+"
#define CODE_MOD_NUMPLAYERS "#MOD_NUMPLAYERS"
#define NUMPLAYERS_PATTERN "[2-4]"

enum GameManagerState {
  DEFAULT,
  PLAYING,
  QUIT,
  GAMEOVER
};

class GameManager {
  private:
    void parseCommand(std::string command);
    void doQuit();
    void doSave(std::string path);
    void doPlaceTile(std::string tile, std::string position);
    void doReplaceTile(std::string tile);
    void doEndTurn();
    GameState* gameState;
    GameManagerState status = DEFAULT;
    bool showRoundOutput = true;
    bool multiPlace;
    bool imatch(std::string s, std::string pattern);

  public:
    GameManager(); ~GameManager();
    void startGame();
    void newGame(std::vector<std::string>, bool multiPlace);
    void loadGame(std::string fileName, int numPlayers, bool multiPlace);
};
