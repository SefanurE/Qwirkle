#include "Menu.h"

// Menu::Menu() {
//     menuOption = "";
// }

void Menu::displayMenu() {
    std::cout << std::endl << "Welcome to Qwirkle!" << std::endl;
    std::cout << "-------------------" << std::endl << std::endl;

    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits" << std::endl;
    std::cout << "4. Quit" << std::endl << std::endl;
    
    std::cout << "> ";
    std::cin >> menuOption;
    std::cout << std::endl;

    bool quit = false;
    while (!quit && !std::cin.eof()) {
        if (menuOption == NEW_GAME) {

        }
        else if (menuOption == LOAD_GAME) {

        }
        else if (menuOption == CREDITS) {

        }
        else if (menuOption == QUIT) {
            quit = true;
        }
        else {
            std::cout << "Invalid input" << std::endl;
            std::cout << "> ";
            std::cin >> menuOption;
            std::cout << std::endl;
        }
    }
    

}