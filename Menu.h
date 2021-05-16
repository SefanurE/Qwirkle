#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>

#define NEW_GAME_OPTION  "1"
#define LOAD_GAME_OPTION "2"
#define CREDITS_OPTION   "3"
#define QUIT_OPTION      "4"

class Menu {
  public:
    void mainMenu();

  private:
    void displayMenu();
    void newGame();
    std::string getNameInput();
    void loadGame();
    void printCredits();
};
