#include <iostream>
#include <vector>
#include <string>

enum GameManagerState {
  DEFAULT,
  PLAYING
};

class GameManager {

  GameManagerState gameState = DEFAULT;

  private:
    void parseCommand(std::istream in);
  
  public:
    void startGame();
    void loadGameSave(std::string path);
};
