#ifndef COSC_ASSIGN_TWO_TILEBAG
#define COSC_ASSIGN_TWO_TILEBAG
#include "LinkedList.h"

class TileBag {
private:
  LinkedList* tiles;
public:
  TileBag();
  void shuffle();
  Tile* draw();
  LinkedList* getList();
};

#endif //COSC_ASSIGN_TWO_TILEBAG