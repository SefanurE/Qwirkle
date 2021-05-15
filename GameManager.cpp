#include "GameManager.h"
#include <regex>
#include <fstream>

GameManager::GameManager() {}

GameManager::~GameManager() {
  delete gameState;
}

/*
 * Method Name: startGame
 * Purpose: Starts a new game and takes input of commands from player to be
 * executed on the gameState
 * Parameters: N/A
 * Return: void
 */
void GameManager::startGame() {
  // Read and parse commands till the player quits
  status = PLAYING;
  while (status == PLAYING) {
    if (showRoundOutput) {
      gameState->showBeforeRoundOutput();
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

    // Did they win?
    Player* winner = gameState->getWinningPlayer();
    if (winner != nullptr) {
      status = GAMEOVER;
      gameState->showAfterGameOutput();
    }
  }
}

/*
 * Method Name: newGame
 * Purpose: Creates a new gameState with the provided player names and begins
 * play on that gamestate
 * Parameters:
 * playerNames [string*] - Array of playerNames
 * Return: void
 */
void GameManager::newGame(std::string playerNames[PLAYER_COUNT]) {
  gameState = new GameState(playerNames);
  startGame();
}

/*
 * Method Name: loadGame
 * Purpose: Reads save data from fileName and creates gameState with provided
 * save information before starting new game.
 * Parameters:
 * fileName [string] - File path to save file
 * Return: void
 */
void GameManager::loadGame(std::string fileName) {
  std::ifstream gameData(fileName);
  if (gameData.is_open()) {
    gameState = new GameState(gameData);
    startGame();
    gameData.close();
  } else {
    std::cout << "Failed to read" << std::endl;
    std::cout << std::endl;
  }
}

/*
 * Method Name: parseCommand
 * Purpose: Interprets, validates and executes commands entered by player
 * on the gameState
 * Parameters:
 * command [string] - Command entered by player
 * Return: void
 */
void GameManager::parseCommand(std::string command) {
  // Parse the command character by character and keep track of what
  // command is being executed and what arguments we have seen so far
  std::string buffer = "";
  std::string comm = "";
  std::vector<std::string> args;
  bool invalid = false;
  bool completedCommand = false;
  for (size_t i = 0; !completedCommand && i < command.length(); i++) {
    char c = command[i];
    if (!std::isspace(c)) {
      buffer.push_back(c);
    }

    // Once we get to a natural break...
    if (std::isspace(c) || i == command.length() - 1) {

      if (buffer != "") {
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
            invalid = true;
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
            invalid = true;
            completedCommand = true;
          }
        } else if (comm == COMM_REPLACE) {
          // Parse the REPLACE command arguments
          // of the form REPLACE [TILE]
          if (imatch(buffer, COMM_TILE)) {
            doReplaceTile(buffer);
            completedCommand = true;
          } else {
            invalid = true;
            completedCommand = true;
          }
        } else {
          invalid = true;
          completedCommand = true;
        }

        // reset buffer
        buffer.clear();
      }
    }
  }

  // Report on unfinished commands
  if (comm != "" && !completedCommand) {
    invalid = true;
  }

  if (invalid) {
    std::cout << "Invalid Input" << std::endl;
  }
}

/*
 * Method Name: imatch
 * Purpose: Checks if a given string complies with a given regex pattern
 * Parameters:
 * checkString [string] - String to run though regex check
 * checkString [string] - Pattern to match passes string to
 * Return: bool - If passed string passes the regex [true] or not [false]
 */
bool GameManager::imatch(std::string checkString, std::string pattern) {
  return std::regex_match(checkString, std::regex(pattern, std::regex_constants::icase));
}

/*
 * Method Name: doQuit
 * Purpose: Updates status to QUIT so gameManager will no longer continue game
 * loop
 * Parameters: N/A
 * Return: void
 */
void GameManager::doQuit() {
  std::cout << std::endl;
  status = QUIT;
}

/*
 * Method Name: doSave
 * Purpose: Create new stream with given file name and pass to gameState to
 * serialise
 * Parameters:
 * fileName [string] - File path (excluding file type) of save location
 * Return: void
 */
void GameManager::doSave(std::string fileName) {
  fileName = fileName + ".save";
  std::ofstream save(fileName);
  save << gameState->serialise();
  save.close();
  std::cout << std::endl << "Game successfully saved" << std::endl;
}

/*
 * Method Name: doPlaceTile
 * Purpose: Ensure command format is correct and execute doPlaceTile on
 * gameState. Updates success tracker based on outcome.
 * Parameters:
 * tile [string] - Tile code to be placed
 * position [string] - Location on board tile will be placed
 * Return: void
 */
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

/*
 * Method Name: doReplaceTile
 * Purpose: Ensure command format is correct and execute doReplaceTile on
 * gameState. Updates success tracker based on outcome.
 * Parameters:
 * tile [string] - Tile code to attempt to replace (Should be in hand)
 * Return: void
 */
void GameManager::doReplaceTile(std::string tile) {
  // Ensure uppercase tile
  for (size_t i = 0; i < tile.length(); i++) {
    tile[i] = std::toupper(tile[i]);
  }

  // Replace the tile
  bool success = gameState->doReplaceTile(tile);
  showRoundOutput = success;
}

bool GameManager::testSaveFileValidity(std::string path) {
  bool valid = true; 
  
  // Validate path
  valid = valid && std::regex_match(path, std::regex(PATH_PATTERN)); 

  // Validate file
  if (valid) {
    std::ifstream gameData(path);
    if (gameData.is_open()) {
      valid = GameState::testSaveFileValidity(gameData);
      if (!valid) {
        std::cout << "Invalid save format" << std::endl;
      }
      gameData.close();
    } else {
      valid = false;
      std::cout << "Can't read file" << std::endl;
    }
  } else {
    std::cout << "Invalid file path" << std::endl;
  }

  return valid;
}
