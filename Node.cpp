
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other)
{
   tile = other.tile;
   next = other.next;
}

Node::~Node() {

}

std::string Node::toString() {
  return "Tile: " + tile->toString() + ", Next: " + next->tile->toString();
}