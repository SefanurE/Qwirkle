#include "GameManager.h"

GameManager::GameManager() {}

void GameManager::startGame() {
  state = PLAYING;
  while (true) {
    // Read in a command
    std::cout << PROMPT;
    std::string command;
    while (true) {
      char c = std::cin.get();
      if (c == EOF) {
        state = QUIT;
        break;
      } else if (c == '\n') {
        break;
      } else {
        command.push_back(c);
      }
    }
    
    // Did we quit?
    if (state != PLAYING) {
      break;
    }

    std::cout << "Got command " << command << std::endl;

    // Parse the command
    parseCommand(command);
  }
}

void GameManager::loadGameSave(std::string path) {

}

void GameManager::parseCommand(std::string command) {
  // Tokenise 
 
  // Parse
}
