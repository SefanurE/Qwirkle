#include "GameManager.h"
#include <regex>
#include <fstream>

GameManager::GameManager() {}

GameManager::~GameManager() {
  delete gameState;
}

void GameManager::startGame() {
  state = PLAYING;
  while (state == PLAYING) {
    // Read in a command
    std::cout << PROMPT;
    std::string command;
    bool readCommand = true;
    while (readCommand) {
      char c = std::cin.get();
      if (c == EOF) {
        state = QUIT;
        readCommand = false;
      } else if (c == '\n') {
        readCommand = false;
      } else {
        command.push_back(c);
      }
    }
    
    // Did we not quit?
    if (state == PLAYING) {
      parseCommand(command);
    }
  }
}

void GameManager::newGame(std::string player1Name, std::string player2Name) {
  std::cout << "starting game w/ players" << player1Name << player2Name << std::endl;
  gameState = new GameState(player1Name, player2Name);
  startGame();
}

void GameManager::loadGame(std::string fileName) {
  std::ifstream gameData(fileName);
  if (gameData.is_open()) {
    gameState = new GameState(gameData);
    startGame();
  }
  else {
    std::cout << "Failed to read" << std::endl;
  }
}

void GameManager::parseCommand(std::string command) {
  std::string buffer = "";
  std::string comm = "";
  std::vector<std::string> args;
  for (size_t i = 0; i < command.length(); i++) {
    char c = std::tolower(command[i]);
    if (!std::isspace(c)) {
      buffer.push_back(c);
    }
    if (std::isspace(c) || i == command.length() - 1) {
      if (comm == "") {
        if (std::regex_match(buffer, std::regex("quit"))) {
          doQuit();
        } else if (std::regex_match(buffer, std::regex("save"))) {
          comm = "save";
        } else if (std::regex_match(buffer, std::regex("place"))) {
          comm = "place";
        } else if (std::regex_match(buffer, std::regex("replace"))) {
          comm = "replace";
        } else {
          std::cerr << "Unrecognised command '" << buffer << "'" << std::endl;
        }
      } else if (comm == "save") {
        doSave(buffer);
      } else if (comm == "place") {
        if (args.size() == 0 && std::regex_match(buffer, std::regex("[a-z][0-9]"))) {
          args.push_back(buffer);
        } else if (args.size() == 1 && std::regex_match(buffer, std::regex("at"))) {
          args.push_back(buffer);
        } else if (args.size() == 2 && std::regex_match(buffer, std::regex("[a-z][0-9]"))) {
          doPlaceTile(args[0], buffer);
        } else {
          std::cerr << "Malformed " << comm << " command." << std::endl;
        }
      } else if (comm == "replace") {
        if (std::regex_match(buffer, std::regex("[a-z][0-9]"))) {
          doReplaceTile(buffer);
        } else {
          std::cerr << "Malformed " << comm << " command." << std::endl;
        }
      } else {
        std::cerr << "Malformed " << comm << " command." << std::endl;
      }

      // reset buffer
      buffer.clear();
    }
  }
}

void GameManager::doQuit() {
  std::cout << "Goodbye" << std::endl;
  state = QUIT;
}

void GameManager::doSave(std::string path) {
  std::cout << "TODO: SAVE to '" << path << "'" << std::endl;
}

void GameManager::doPlaceTile(std::string tile, std::string position) {

  std::cout << "TODO: IMPL PLACE " << tile << " to " << position << "'" << std::endl;
}

void GameManager::doReplaceTile(std::string tile) {
  std::cout << "TODO: IMPL REPLACE " << tile << std::endl;
  // TODO: call to game state 
}
