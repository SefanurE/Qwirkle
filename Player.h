#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER

#include "LinkedList.h"
#include "TileBag.h"

#define HANDSIZE 6

class Player {
  private:
    std::string name;
    LinkedList* hand;
    int score;
    bool isAI;

  public:
    Player();
    ~Player();
    Player(std::string name, bool isAI);
    std::string getName();
    LinkedList* getHand();
    void setScore(int score);
    void addScore(int newScore);
    int getScore();
    void initHand(TileBag* bag);
    bool getIsAI();
};

#endif //COSC_ASSIGN_TWO_PLAYER
