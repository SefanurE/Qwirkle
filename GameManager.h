#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "TileBag.h"
#include "GameState.h"
#include "Board.h"
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
    GameState* gameState;

  public:
    GameManager();
    void startGame();
    void newGame(std::string player1Name, std::string player2Name);
    void loadGame(std::string fileName);
};
