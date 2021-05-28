#include "Node.h"

/*
 * Constructor Name: ode
 * Purpose: Instantiates the tile within the node and pointer to the next node
 * in the list
 * Parameters:
 * tile [Tile*] - Pointer to tile to be within the node
 * next [Node*] - Pointer to next node in the list
 * Return: N/A
 */
Node::Node(Tile* tile, Node* next) {
  this->tile = tile;
  this->next = next;
}

/*
 * Constructor Name: Node
 * Purpose: Constructs a node from another provided node
 * Parameters:
 * other [Node&] - Reference to another node to copy
 * Return: N/A
 */
Node::Node(Node &other) {
  tile = other.tile;
  next = other.next;
}


Node::~Node() {}
