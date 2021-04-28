
#include <iostream>

#define NEW_GAME  "1"
#define LOAD_GAME "2"
#define CREDITS   "3"
#define QUIT      "4"

class Menu {
public:
    // Menu();
    void displayMenu();

private:
    std::string menuOption;
};
