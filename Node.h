
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include <string>
#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next);
   Node(Node& other);
   ~Node();
   std::string toString();

   Tile*    tile;
   Node*    next;
};

#endif // ASSIGN2_NODE_H
