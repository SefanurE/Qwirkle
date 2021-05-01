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