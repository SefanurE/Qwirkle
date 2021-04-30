
#include <iostream>
#include <cstring>
#include <cctype>

#define NEW_GAME  "1"
#define LOAD_GAME "2"
#define CREDITS   "3"
#define QUIT      "4"

class Menu {
public:
    // Menu();
    void mainMenu();
    

private:
    void displayMenu();
    void newGame();
    std::string getNameInput();
    void loadGame();
    void printCredits();

    std::string menuOption;
};
