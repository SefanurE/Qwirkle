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
#define NUM_PLACED_TILES_PATTERN "[0-6]"
#define COLROW_PATTERN "^[a-zA-Z ]-?[0-9]+$"
#define CLA_3_PLAYERS "--3players"
#define CLA_4_PLAYERS "--4players"
#define CLA_MULTI_PLACE "--multi"
#define CLA_COLOUR "--colour"

class Menu {
  public:
    void mainMenu(int numPlayers, bool multiPlace, bool coloured);

  private:
    void displayMenu();
    void newGame(int numPlayers, bool multiPlace, bool coloured);
    int getNumPlayers();
    std::string getNameInput();
    std::string getMenuOption();
    void loadGame(int numPlayers, bool multiPlace, bool coloured);
    void printCredits();
    bool testSaveFileValidity(std::string path, int numPlayers, bool multiPlace);
};
