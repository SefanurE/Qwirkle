#include <iostream>
#include <vector>
#include <string>

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
  
  public:
    GameManager();
    void startGame();
    void loadGameSave(std::string path);
};
