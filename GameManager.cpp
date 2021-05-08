#include "GameManager.h"
#include <regex>
#include <fstream>

GameManager::GameManager() {}

GameManager::~GameManager() {
  delete gameState;
}

void GameManager::startGame() {
  status = PLAYING;
  while (status == PLAYING) {
    if (showRoundOutput) {
      gameState->showBeforeRoundOutput();
    } else {
      std::cout << std::endl;
    }
    std::cout << PROMPT;
    std::string command;
    bool readCommand = true;
    while (readCommand) {
      char c = std::cin.get();
      if (c == EOF) {
        status = QUIT;
        readCommand = false;
      } else if (c == '\n') {
        readCommand = false;
      } else {
        command.push_back(c);
      }
    }
    
    // Did we not quit?
    if (status == PLAYING) {
      showRoundOutput = false;
      parseCommand(command);
    }
  }
}

void GameManager::newGame(std::string player1Name, std::string player2Name) {
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
    char c = std::toupper(command[i]);
    if (!std::isspace(c)) {
      buffer.push_back(c);
    }
    if (std::isspace(c) || i == command.length() - 1) {
      if (comm == "") {
        if (std::regex_match(buffer, std::regex(COMM_QUIT))) {
          doQuit();
        } else if (std::regex_match(buffer, std::regex(COMM_SAVE))) {
          comm = COMM_SAVE;
        } else if (std::regex_match(buffer, std::regex(COMM_PLACE))) {
          comm = COMM_PLACE;
        } else if (std::regex_match(buffer, std::regex(COMM_REPLACE))) {
          comm = COMM_REPLACE;
        } else {
          std::cerr << "Unrecognised command '" << buffer << "'" << std::endl;
        }
      } else if (comm == COMM_SAVE) {
        doSave(buffer);
      } else if (comm == COMM_PLACE) {
        if (args.size() == 0 && std::regex_match(buffer, std::regex(COMM_TILE))) {
          args.push_back(buffer);
        } else if (args.size() == 1 && std::regex_match(buffer, std::regex(COMM_AT))) {
          args.push_back(buffer);
        } else if (args.size() == 2 && std::regex_match(buffer, std::regex(COMM_TILE))) {
          doPlaceTile(args[0], buffer);
        } else {
          std::cerr << "Malformed " << comm << " command." << std::endl;
        }
      } else if (comm == COMM_REPLACE) {
        if (std::regex_match(buffer, std::regex(COMM_TILE))) {
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
  status = QUIT;
}

void GameManager::doSave(std::string path) {
  std::cout << "TODO: SAVE to '" << path << "'" << std::endl;
}

void GameManager::doPlaceTile(std::string tile, std::string position) {
  bool success = gameState->doPlaceTile(tile, position);
  showRoundOutput = success;
}

void GameManager::doReplaceTile(std::string tile) {
  bool success = gameState->doReplaceTile(tile);
  showRoundOutput = success;
}
