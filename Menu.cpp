#include "Menu.h"

// Menu::Menu() {
//     menuOption = "";
// }

void Menu::mainMenu() {
    std::cout << std::endl 
              << "Welcome to Qwirkle!" << std::endl
              << "-------------------" << std::endl;
    displayMenu();

    bool quit = false;
    while (!quit && !std::cin.eof()) {
        std::cout << "> ";
        std::cin >> menuOption;
        std::cout << std::endl;
        if (menuOption == NEW_GAME) {
            newGame();
        }
        else if (menuOption == LOAD_GAME) {
            loadGame();
        }
        else if (menuOption == CREDITS) {
            printCredits();
            displayMenu();
        }
        else if (menuOption == QUIT) {
            std::cout << "Goodbye" << std::endl;
            quit = true;
        }
        else {
            std::cout << "Invalid input, try again" << std::endl;
        }
    } 
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
    // std::string player1Name = "";
    // std::string player2Name = "";

    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a name for player 1 (uppercase letters only)" << std::endl;
    std::string player1Name = getNameInput();

    std::cout << std::endl;
    std::cout << "Enter a name for player 2 (uppercase letters only)" << std::endl;
    std::string player2Name = getNameInput();

    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;
}

std::string Menu::getNameInput() {
    std::string playerName = "";
    bool exitWhile = false;
    bool nameIsOnlyUppercase = true;
    while (!exitWhile && !std::cin.eof()) {
        std::cout << "> ";
        std::cin >> playerName;

        char arrPlayerName[playerName.size()+1];
        strcpy(arrPlayerName, playerName.c_str());

        // Checks if each character is a letter then uppercase letter
        for (size_t i = 0; i < strlen(arrPlayerName); ++i) {
            if (!isalpha(arrPlayerName[i])) {
                nameIsOnlyUppercase = false;
            }
            else if (arrPlayerName[i] != toupper(arrPlayerName[i])) {
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