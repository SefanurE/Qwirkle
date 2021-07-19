#include "Menu.h"
#include "GameManager.h"

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
    std::cout << PROMPT;
    std::string menuOption = "";
    bool read = true;
    // Check each character input by user
    while (read) {
      char c = std::cin.get();
      if (c == '\n') {
        read = false;
      } else if (c == EOF) {
        std::cout << std::endl << std::endl;
        read = false;
        quit = true;
      // If c isn not \n, EOF or a space add to menuOption string
      } else if (!std::isspace(c)) {
        menuOption.push_back(c);
      }
    }

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
    } else if (menuOption == COLOUR_OPTION) {
      // Switches coloured value
      coloured = !coloured;
      displayMenu();
    } else if (menuOption == QUIT_OPTION) {
      std::cout << std::endl;
      quit = true;
    } else if (!quit) {
      std::cout << "Try a number displayed on the menu (1, 2, 3, 4 or 5)"
                << std::endl;
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
            << "4. Toggle colour " << colouredStatus() << std::endl
            << "5. Quit" << std::endl << std::endl;
}

/*
 * Method Name: colouredStatus
 * Purpose: Return string representation of coloured value
 * Parameters: N/A
 * Return: string - Represents whether the coloured option is on or off
 */
std::string Menu::colouredStatus() {
  std::string status = "";
  if (coloured) {
    status = GREEN_TXT;
    status += "[ON]";
  } else {
    status = RED_TXT;
    status += "[OFF]";
  }
  status += RESET_TXT;
  return status;
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
  int playerCount = 0;
  std::cout << std::endl
            << "Starting a New Game" << std::endl;
  std::cout << std::endl
            << "Enter the number of players (2, 3 or 4)" << std::endl;
  std::string playerCountStr = getPlayerCountInput();
  // Did the user input EOF
  if (playerCountStr != "") {
    playerCount = stoi(playerCountStr);
  } else {
    cancel = true;
  }

  std::string playerNames[playerCount] = {"0"}; 
  if (!cancel) {
    std::cout << std::endl
                << "(Put 'AI ' at the start of the name to have an AI player)"
                << std::endl;
    // Ask user for each players' name
    for (int i = 0; !cancel && i < playerCount; i++) {
      std::cout << std::endl;
      std::cout << "Enter a name for player " << i + 1
                << " (uppercase letters only)" << std::endl;
      playerNames[i] = getNameInput();
      // Did the user input EOF
      if (playerNames[i] == "") {
        cancel = true;
      }
    }
  }

  if (!cancel) {
    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;

    // Create new gameManager and begin a new game with the player names
    GameManager* gameManager = new GameManager();
    gameManager->newGame(playerNames, playerCount, coloured);

    // Game is over, cleanup
    delete gameManager;
  }
}

/*
 * Method Name: getPlayerCount
 * Purpose: Requests and validates player count from user
 * Parameters: N/A
 * Return: int - Validated player count
 */
std::string Menu::getPlayerCountInput() {
  std::string playerCountStr = "";
  bool done = false;
  // Keep getting a player count from the user until it is valid
  while (!done) {
    std::cout << PROMPT;
    playerCountStr = "";
    bool read = true;
    // Check each character input by user
    while (read) {
      char c = std::cin.get();
      if (c == '\n') {
        read = false;
        // Make sure the player count has one character
        if (playerCountStr.length() == 1) {
          done = true;
        } else {
          std::cout << "Number of players must be 2, 3 or 4"
                    << std::endl;
        }
      // Quit program if c is EOF
      } else if (c == EOF) {
        std::cout << std::endl << std::endl;
        read = false;
        done = true;
        // playerCountStr = "";
      // Checks if c is a character other than 2, 3 or 4
      } else if (c < MIN_PLAYER_COUNT || c > MAX_PLAYER_COUNT) {
        // Clears user input to check the player count input
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Number of players must be 2, 3 or 4"
                  << std::endl;
        read = false;
        done = false;
      } else {
        playerCountStr.push_back(c);
      }
    }
  }
  return playerCountStr;
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
    std::cout << PROMPT;
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
        // playerName = "";
      // Checks if c is a character other than a capital letter
      } else if ((c < 'A' || c > 'Z') && !(c == ' ' && playerName == "AI")) {
        // Clears user input to check the new name input
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Name must only be uppercase letters, enter new name"
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
  GameManager* gameManager = new GameManager();

  std::string fileName = "";
  bool done = false;
  bool quit = false;
  while (!done) {
    std::cout << std::endl;
    std::cout << "Enter the filename from which to load a game" << std::endl;
    std::cout << PROMPT;
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
        done = gameManager->testSaveFileValidity(fileName);
      } else {
        fileName.push_back(c);
      }
    }
  }

  if (!quit) {
    // Load game from file
    gameManager->loadGame(fileName, coloured);
  }

  // Game is over, cleanup
  delete gameManager;
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
