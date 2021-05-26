#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>

#define NEW_GAME_OPTION  "1"
#define LOAD_GAME_OPTION "2"
#define CREDITS_OPTION   "3"
#define QUIT_OPTION      "4"
#define TWO_PLAYER_OPTION "1"
#define THREE_PLAYER_OPTION "2"
#define FOUR_PLAYER_OPTION "3"
#define PENDING_INPUT -1
#define VAR_PLAYERS_FALSE "1"
#define VAR_PLAYERS_TRUE "2"

class Menu {
  public:
    void mainMenu();

  private:
    void displayMenu();
    void newGame();
    int getNumPlayers();
    std::string getNameInput();
    std::string getMenuOption();
    void loadGame();
    void printCredits();
    bool testSaveFileValidity(std::string path, bool varPlayers);
};
