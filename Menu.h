#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>

#define NEW_GAME_OPTION  "1"
#define LOAD_GAME_OPTION "2"
#define CREDITS_OPTION   "3"
#define COLOUR_OPTION    "4"
#define QUIT_OPTION      "5"
#define MIN_PLAYER_COUNT '2'
#define MAX_PLAYER_COUNT '4'

class Menu {
  public:
    void mainMenu();

  private:
    bool coloured;
    
    void displayMenu();
    std::string colouredStatus();
    void newGame();
    std::string getPlayerCountInput();
    std::string getNameInput();
    void loadGame();
    void printCredits();
};
