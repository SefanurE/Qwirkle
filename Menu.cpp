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
        std::cout << "> ";
        std::string menuOption = "";
        bool read = true;
        while (read) {
          char c = std::cin.get();
          if (c == '\n') {
            read = false;
          } else if (c == EOF) {
            std::cout << std::endl;
            read = false;
            quit = true;
          } else if (!std::isspace(c)) {
            menuOption.push_back(c);
          }
        }

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
    std::string playerNames[PLAYER_COUNT] = {"0"};
    for (int i = 0; !cancel && i < PLAYER_COUNT; i++) {
        std::cout << std::endl;
        std::cout << "Enter a name for player " << i + 1 
                  << " (uppercase letters only)" << std::endl;
        playerNames[i] = getNameInput();
        if (playerNames[i] == "") {
          cancel = true;
        }
    }

    if (!cancel) {
      std::cout << std::endl;
      std::cout << "Let's Play!" << std::endl;

      GameManager* gameManager = new GameManager();
      gameManager->newGame(playerNames);

      // Game is over, cleanup
      delete gameManager;
    }
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
    while (!done) {
        std::cout << "> ";
        playerName = "";
        bool read = true;
        while (read) {
          char c = std::cin.get();
          if (c == '\n') {
            read = false;
            if (playerName.length() > 0) {
              done = true;
            }
          } else if (c == EOF) {
            std::cout << std::endl << std::endl;
            read = false;
            done = true;
            playerName = "";
          } else if (c < 'A' || c > 'Z') {
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
    while (read) {
      char c = std::cin.get();
      if (c == EOF) {
        std::cout << std::endl << std::endl;
        read = false;
        done = true;
        quit = true;
      } else if (c == '\n') {
        read = false;
        done = true; // TODO: gameManager->testFileValidity(fileName);
      } else {
        fileName.push_back(c);
      }
    }
  }

  if (!quit) {
    gameManager->loadGame(fileName);
  }

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
