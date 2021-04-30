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
  
  public:
    GameManager();
    void startGame();
    void loadGameSave(std::string path);
};
