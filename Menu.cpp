#include "Menu.h"
#include "GameManager.h"
#include <regex>

/*
 * Method Name: mainMenu
 * Purpose: Begins requesting input from user as to what action they wish to
 * complete and executes commands as requested.
 * Parameters: N/A
 * Return: N/A
 */
void Menu::mainMenu() {
  std::cout << std::endl
    << "Welcome to Qwirkle!" << std::endl
    << "-------------------" << std::endl;
  displayMenu();

  bool quit = false;
  while (!quit && !std::cin.eof()) {
    std::string menuOption = getMenuOption();
    // Check for which menu option was selected
    if (menuOption == NEW_GAME_OPTION) {
      newGame();
      quit = true;
    } else if (menuOption == LOAD_GAME_OPTION) {
      loadGame();
      quit = true;
    } else if (menuOption == CREDITS_OPTION) {
      printCredits();
      displayMenu();
    } else if (menuOption == QUIT_OPTION) {
      std::cout << std::endl;
      quit = true;
    } else if (!quit) {
      std::cout << "Invalid input, try again" << std::endl;
    }
  }
  std::cout << "Goodbye" << std::endl;
}

/*
 * Method Name: displayMenu
 * Purpose: Displays menu options to user
 * Parameters: N/A
 * Return: N/A
 */
void Menu::displayMenu() {
  std::cout << std::endl
            << "Menu" << std::endl
            << "----" << std::endl
            << "1. New Game" << std::endl
            << "2. Load Game" << std::endl
            << "3. Credits" << std::endl
            << "4. Quit" << std::endl << std::endl;
}

/*
 * Method Name: newGame
 * Purpose: Retrieves player names from user and creates new gameManager
 * instance for newGame to be called on
 * Parameters: N/A
 * Return: N/A
 */
void Menu::newGame() {
  bool cancel = false;
  std::cout << std::endl;
  std::cout << "Starting a New Game" << std::endl;
  std::cout << std::endl << "Select how many players" << std::endl;
  std::cout << "1. 2 players" << std::endl;
  std::cout << "2. 3 players" << std::endl;
  std::cout << "3. 4 players" << std::endl;
  int numPlayers = PENDING_INPUT;
  while (numPlayers == PENDING_INPUT && !cancel) {
    std::string playerCountOption = getMenuOption();
    if (playerCountOption == TWO_PLAYER_OPTION) {
      numPlayers = 2;
    } else if (playerCountOption == THREE_PLAYER_OPTION) {
      numPlayers = 3;
    } else if (playerCountOption == FOUR_PLAYER_OPTION) {
      numPlayers = 4;
    } else if (playerCountOption == QUIT_OPTION) {
      cancel = true;
    }
  }

  if (!cancel) {
    std::vector<std::string> playerNames(numPlayers, "");
    // Ask user for each players' name
    for (int i = 0; !cancel && i < numPlayers; i++) {
      std::cout << std::endl;
      std::cout << "Enter a name for player " << i + 1
                << " (uppercase letters only)" << std::endl;
      playerNames[i] = getNameInput();
      // Did the user input EOF
      if (playerNames[i] == "") {
        cancel = true;
      }
    }

    if (!cancel) {
      std::cout << std::endl;
      std::cout << "Let's Play!" << std::endl;

      // Create new gameManager and begin a new game with the player names
      GameManager* gameManager = new GameManager();
      gameManager->newGame(playerNames);

      // Game is over, cleanup
      delete gameManager;
    }
  }
}

std::string Menu::getMenuOption() {
  std::cout << "> ";
  std::string menuOption = "";
  bool read = true;
  // Check each character input by user
  while (read) {
    char c = std::cin.get();
    if (c == '\n') {
      read = false;
    } else if (c == EOF) {
      std::cout << std::endl;
      read = false;
      menuOption = QUIT_OPTION;
      // If c isn not \n, EOF or a space add to menuOption string
    } else if (!std::isspace(c)) {
      menuOption.push_back(c);
    }
  }
  return menuOption;
}

/*
 * Method Name: getNameInput
 * Purpose: Requests and validates name input from user
 * Parameters: N/A
 * Return:
 * string - Validated player name
 */
std::string Menu::getNameInput() {
  std::string playerName = "";
  bool done = false;
  // Keep getting a player name from the user until it is valid (only caps)
  while (!done) {
    std::cout << "> ";
    playerName = "";
    bool read = true;
    // Check each character input by user
    while (read) {
      char c = std::cin.get();
      if (c == '\n') {
        read = false;
        // Make sure the player name atleast has one character
        if (playerName.length() > 0) {
          done = true;
        }
      // Quit program if c is EOF
      } else if (c == EOF) {
        std::cout << std::endl << std::endl;
        read = false;
        done = true;
        playerName = "";
      // Checks if c is a character other than a capital letter
      } else if (c < 'A' || c > 'Z') {
        // Clears user input to check the new name input
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Name must be only uppercase letters, enter new name"
                  << std::endl;
        read = false;
        done = false;
      } else {
        playerName.push_back(c);
      }
    }
  }
  return playerName;
}

/*
 * Method Name: loadGame
 * Purpose: Requests save file path and creates new gameManager instance for
 * load game to be called on
 * Parameters: N/A
 * Return: N/A
 */
void Menu::loadGame() {
  // Create new gameManager

  bool varPlayers = false;
  bool done = false;
  bool cancel = false;
  std::cout << "What kind of save would you like to load?" << std::endl;
  std::cout << "1. 2 Players" << std::endl;
  std::cout << "2. 3-4 Players" << std::endl;
  while (!done && !cancel) {
    std::string varPlayersOption = getMenuOption();
    if (varPlayersOption == VAR_PLAYERS_FALSE) {
      varPlayers = false;
      done = true;
    } else if (varPlayersOption == VAR_PLAYERS_TRUE) {
      varPlayers = true;;
      done = true;
    } else if (varPlayersOption == QUIT_OPTION) {
      cancel = true;
    }
  }

  if (!cancel) {
    GameManager* gameManager = new GameManager();

    std::string fileName = "";
    bool done = false;
    bool quit = false;
    while (!done) {
      std::cout << std::endl;
      std::cout << "Enter the filename from which load a game: " << std::endl;
      std::cout << "> ";
      fileName = "";
      bool read = true;
      // Check each character input by user
      while (read) {
        char c = std::cin.get();
        // Quit program if c is EOF
        if (c == EOF) {
          std::cout << std::endl << std::endl;
          read = false;
          done = true;
          quit = true;
        } else if (c == '\n') {
          read = false;
          // Check validity of file name input by user
          done = testSaveFileValidity(fileName, varPlayers);
        } else {
          fileName.push_back(c);
        }
      }
    }

    if (!quit) {
      // Load game from file
      gameManager->loadGame(fileName, varPlayers);
    }

    // Game is over, cleanup
    delete gameManager;
  }
}

/*
 * Method Name: printCredits
 * Purpose: Prints program author details
 * Parameters: N/A
 * Return: N/A
 */
void Menu::printCredits() {
  std::cout << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "Name: Maxwell Reid" << std::endl
            << "Student ID: s3787033" << std::endl
            << "Email: s3787033@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;
  std::cout << "Name: Ewan Breakey" << std::endl
            << "Student ID: s3845382" << std::endl
            << "Email: s3845382@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;
  std::cout << "Name: Sefaur Erciyas" << std::endl
            << "Student ID: s3842307" << std::endl
            << "Email: s3842307@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;
  std::cout << "Name: Sivan Krispin" << std::endl
            << "Student ID: s3856571" << std::endl
            << "Email: s3856571@student.rmit.edu.au" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
}

bool Menu::testSaveFileValidity(std::string path, bool varPlayers) {
  bool valid = true;

  // Validate path
  valid = valid && std::regex_match(path, std::regex(PATH_PATTERN));

  // Validate file
  if (valid) {
    std::ifstream gameData(path);
    std::string line = "";
    if (gameData.is_open()) {
      int numPlayers = 2;
      if (varPlayers) {
        getline(gameData, line);
        if (std::regex_match(line, std::regex(NUMPLAYERS_PATTERN))) {
          numPlayers = stoi(line);
        }
      }

      std::vector<std::string> patterns(numPlayers * 3 + 4, "");

      // Add player patterns
      for (int i = 0; i < numPlayers; i++) {
        patterns[i * 3] = NAME_PATTERN;
        patterns[i * 3 + 1] = SCORE_PATTERN;
        patterns[i * 3 + 2] = HAND_PATTERN;
      }

      // Add game patterns
      patterns[numPlayers * 3 + 0] = BOARD_SIZE_PATTERN;
      patterns[numPlayers * 3 + 1] = BOARD_TILES_PATTERN;
      patterns[numPlayers * 3 + 2] = BAG_TILES_PATTERN;
      patterns[numPlayers * 3 + 3] = NAME_PATTERN;

      // Check the file against all the patterns, line by line
      getline(gameData, line);
      for (int i = 0; i < numPlayers * 3 + 4; i++) {
        valid = valid && std::regex_match(line, std::regex(patterns[i]));
        getline(gameData, line);
      }
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