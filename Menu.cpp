#include "Menu.h"
#include "GameManager.h"

void Menu::mainMenu() {
    std::cout << std::endl 
              << "Welcome to Qwirkle!" << std::endl
              << "-------------------" << std::endl;
    displayMenu();

    std::string menuOption = "";
    bool quit = false;
    while (!quit && !std::cin.eof()) {
        std::cout << "> ";
        std::cin >> menuOption;
        std::cout << std::endl;
        if (menuOption == NEW_GAME_OPTION) {
            newGame();
        }
        else if (menuOption == LOAD_GAME_OPTION) {
            loadGame();
        }
        else if (menuOption == CREDITS_OPTION) {
            printCredits();
            displayMenu();
        }
        else if (menuOption == QUIT_OPTION) {
            quit = true;
        }
        else {
            std::cout << "Invalid input, try again" << std::endl;
        }
    }
    std::cout << "Goodbye" << std::endl;
}

void Menu::displayMenu() {
    std::cout << std::endl 
              << "Menu" << std::endl
              << "----" << std::endl
              << "1. New Game" << std::endl
              << "2. Load Game" << std::endl
              << "3. Credits" << std::endl
              << "4. Quit" << std::endl << std::endl;
}

void Menu::newGame() {
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a name for player 1 (uppercase letters only)" << std::endl;
    std::string player1Name = getNameInput();

    std::cout << std::endl;
    std::cout << "Enter a name for player 2 (uppercase letters only)" << std::endl;
    std::string player2Name = getNameInput();

    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;

    GameManager* gameManager = new GameManager();
    gameManager->newGame(player1Name, player2Name);
}

std::string Menu::getNameInput() {
    std::string playerName = "";
    bool exitWhile = false;
    bool nameIsOnlyUppercase = true;
    while (!exitWhile && !std::cin.eof()) {
        std::cout << "> ";
        std::cin >> playerName;

        for (char c : playerName) {
            if (c < 'A' || c > 'Z') {
                nameIsOnlyUppercase = false;
            }
        }

        if (!nameIsOnlyUppercase) {
            std::cout << "Name must be only uppercase letters, enter new name" << std::endl;
        }  
        else {
            exitWhile = true;
        }
        nameIsOnlyUppercase = true;
    }
    return playerName;
}

void Menu::loadGame() {
  std::cout << "Enter the filename from which load a game: " << std::endl;
  std::cout << "> ";
  std::string fileName;
  std::cin >> fileName;
  GameManager* gameManager = new GameManager();
  gameManager->loadGame(fileName);
}

void Menu::printCredits() {
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