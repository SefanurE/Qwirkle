#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#define PROMPT "> "

enum GameManagerState {
  DEFAULT,
  PLAYING,
  QUIT
};

class GameManager {

  GameManagerState state = DEFAULT;

  private:
    void parseCommand(std::string command);
    void doQuit();
    void doSave(std::string path);
    void doPlaceTile(std::string tile, std::string position);
    void doReplaceTile(std::string tile);
    Player* players[2];
    TileBag* tileBag;

  public:
    GameManager(Player* player1, Player* player2);
    void startGame();
    void loadGameSave(std::string path);
};
