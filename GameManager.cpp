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
        std::cout << std::endl << std::endl;
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

void GameManager::newGame(std::string playerNames[PLAYER_COUNT]) {
  gameState = new GameState(playerNames);
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
  // Parse the command character by character and keep track of what
  // command is being executed and what arguments we have seen so far
  std::string buffer = "";
  std::string comm = "";
  std::vector<std::string> args;
  bool completedCommand = false;
  for (size_t i = 0; !completedCommand && i < command.length(); i++) {
    char c = command[i];
    if (!std::isspace(c)) {
      buffer.push_back(c);
    }

    // Once we get to a natural break...
    if (std::isspace(c) || i == command.length() - 1) {
      
      // Establish initial command
      if (comm == "") {
        if (imatch(buffer, COMM_QUIT)) {
          doQuit();
        } else if (imatch(buffer, COMM_SAVE)) {
          comm = COMM_SAVE;
        } else if (imatch(buffer, COMM_PLACE)) {
          comm = COMM_PLACE;
        } else if (imatch(buffer, COMM_REPLACE)) {
          comm = COMM_REPLACE;
        } else {
          std::cerr << "Unrecognised command '" << buffer << "'" << std::endl;
          completedCommand = true;
        }
      } else if (comm == COMM_SAVE) {
        // Parse the SAVE Command arguments
        // of the form SAVE [path]
        doSave(buffer);
        completedCommand = true;
      } else if (comm == COMM_PLACE) {
        // Parse the PLACE command arguments
        // of the form "PLACE [TILE] AT [TILE]"
        if (args.size() == 0 && imatch(buffer, COMM_TILE)) {
          args.push_back(buffer);
        } else if (args.size() == 1 && imatch(buffer, COMM_AT)) {
          args.push_back(buffer);
        } else if (args.size() == 2 && imatch(buffer, COMM_TILE)) {
          doPlaceTile(args[0], buffer);
          completedCommand = true;
        } else {
          std::cerr << "Malformed " << comm << " command." << std::endl;
          completedCommand = true;
        }
      } else if (comm == COMM_REPLACE) {
        // Parse the REPLACE command arguments
        // of the form REPLACE [TILE]
        if (imatch(buffer, COMM_TILE)) {
          doReplaceTile(buffer);
          completedCommand = true;
        } else {
          std::cerr << "Malformed " << comm << " command." << std::endl;
          completedCommand = true;
        }
      } else {
        std::cerr << "Malformed " << comm << " command." << std::endl;
        completedCommand = true;
      }

      // reset buffer
      buffer.clear();
    }
  }

  // Report on unfinished commands
  if (comm != "" && !completedCommand) {
    std::cerr << "Incomplete " << comm << " command." << std::endl;
  }
}

bool GameManager::imatch(std::string s, std::string pattern) {
  return std::regex_match(s, std::regex(pattern, std::regex_constants::icase));
}

void GameManager::doQuit() {
  std::cout << std::endl;
  status = QUIT;
}

void GameManager::doSave(std::string fileName) {
  fileName = fileName + ".save";
  std::ofstream save(fileName);
  save << gameState->serialise();
  save.close();
  std::cout << std::endl << "Game successfully saved" << std::endl;
}

void GameManager::doPlaceTile(std::string tile, std::string position) {
  // Ensure uppercase tile
  for (size_t i = 0; i < tile.length(); i++) {
    tile[i] = std::toupper(tile[i]);
  }

  // Ensure uppercase position
  for (size_t i = 0; i < position.length(); i++) {
    position[i] = std::toupper(position[i]);
  }

  // Place the tile
  bool success = gameState->doPlaceTile(tile, position);
  showRoundOutput = success;
}

void GameManager::doReplaceTile(std::string tile) {
  // Ensure uppercase tile
  for (size_t i = 0; i < tile.length(); i++) {
    tile[i] = std::toupper(tile[i]);
  }

  // Replace the tile
  bool success = gameState->doReplaceTile(tile);
  showRoundOutput = success;
}
