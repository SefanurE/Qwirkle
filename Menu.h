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
#define NAME_PATTERN "^[A-Z]+$"
#define SCORE_PATTERN "^\\d+$"
#define HAND_PATTERN "^(([A-Z][0-9]+),)*([A-Z][0-9]+)$|(^$)"
#define BOARD_SIZE_PATTERN "^\\d+,\\d+$"
#define BOARD_TILES_PATTERN "^(([A-Z][0-9]+)@([A-Z][0-9]+),\\s?)*\
([A-Z][0-9]+)@([A-Z][0-9]+)$|(^$)"
#define BAG_TILES_PATTERN "^(([A-Z][0-9]+),)*([A-Z][0-9]+)$|(^$)"
#define NUM_PLAYERS_PATTERN "[2-4]"

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
    bool testSaveFileValidity(std::string path, int &numPlayers);
};
