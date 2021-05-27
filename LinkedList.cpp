#include "LinkedList.h"
#include <iostream>

/*
 * Constructor Name: LinkedList
 * Purpose: Intialises head and size of linked list
 * Parameters: N/A
 * Return: N/A
 */
LinkedList::LinkedList() {
  head = nullptr;
  tail = nullptr;
  size = 0;
}

/*
 * Deconstructor Name: LinkedList
 * Purpose: Deletes all tiles and nodes within the linked list upon deletion
 * Parameters: N/A
 * Return: N/A
 */
LinkedList::~LinkedList() {
  Node* node = head;
  Node* nextNode = nullptr;
  while (node != nullptr) {
    nextNode = node->next;
    delete node->tile;
    delete node;
    node = nextNode;
  }
}

/*
 * Method Name: push
 * Purpose: Pushes a tile to the end of the list
 * Parameters:
 * tile [Tile*] - Pointer to the tile to add to the list
 * Return: N/A
 */
void LinkedList::push(Tile* tile) {
  Node* newNode = new Node(tile, nullptr);
  if (size == 0) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

/*
 * Method Name: pop
 * Purpose: Removes and returns the first item from the linked list
 * Parameters:
 * Return:
 * Tile* - The first tile in the linked list
 */
Tile* LinkedList::pop() {
  return remove(0);;
}

/*
 * Method Name: insertAfter
 * Purpose: Inserts a tile into the list after a given index
 * Parameters:
 * index [int] - Index to insert after
 * tile [Tile*] - Pointer to the tile to add to the list
 * Return: N/A
 */
void LinkedList::insertAfter(int index, Tile* tile) {
  if (index < size - 1) {
    Node* nextNode = getNode(index + 1);
    Node* newNode = new Node(tile, nextNode);
    getNode(index)->next = newNode;
  } else {
    Node* newNode = new Node(tile, nullptr);
    getNode(index)->next = newNode;
    tail = newNode;
  }
  size++;
}

/*
 * Method Name: remove
 * Purpose: Removes and returns a tile at a given index
 * Parameters:
 * index [int] - Index to insert remove
 * Return:
 * Tile* - Removed tile
 */
Tile* LinkedList::remove(int index) {
  Node* removeNode = getNode(index);
  if (index == 0) {
    head = removeNode->next;
  } else {
    getNode(index - 1)->next = removeNode->next;
  }
  if (tail == removeNode) {
    if (index == 0) {
      tail = nullptr;
    } else {
      tail = getNode(index - 1);
    }
  }
  size--;
  Tile* removeTile = removeNode->tile;
  delete removeNode;
  return removeTile;
}

/*
 * Method Name: get
 * Purpose: Returns a tile at a given index of the linkedlist
 * Parameters:
 * index [int] - Index to get tile of
 * Return:
 * Tile* - Tile at index
 */
Tile* LinkedList::get(int index) {
  return getNode(index)->tile;
}

/*
 * Method Name: getNode
 * Purpose: Returns a node at a given index of the linkedlist
 * Parameters:
 * index [int] - Index to get node of
 * Return:
 * Node* - Node at index
 */
Node* LinkedList::getNode(int index) {
  Node* retrieveNode = head;
  for (int i = 0; i < index; i++) {
    retrieveNode = retrieveNode->next;
  }
  return retrieveNode;
}

/*
 * Method Name: toString
 * Purpose: Converts linked list to string for saving and display
 * Parameters: N/A
 * Return:
 * string - All values within linked list comma seperated
 */
std::string LinkedList::toString(bool isColoured) {
  std::string listString = "";
  Node* node = head;
  while (node != nullptr) {
    if (isColoured) {
      listString += node->tile->toDisplayString(isColoured);
    } else {
      listString += node->tile->toString();
    }
    if (node->next != nullptr) {
      listString += ",";
    }
    node = node->next;
  }
  return listString;
}

/*
 * Method Name: getSize
 * Purpose: Retrieves the size of the linked list
 * Parameters: N/A
 * Return:
 * int - Size of the linkedlist
 */
int LinkedList::getSize() {
  return size;
}

/*
 * Method Name: fromString
 * Purpose: Creates linked list from a given string
 * Parameters:
 * listString [string] - String of a linked list from a save file
 * Return:
 */
void LinkedList::fromString(std::string listString) {
  std::string currentBlock = "";
  for (char c : listString) {
    if (c != ',') {
      currentBlock += c;
    } else {
      std::string shapeStr(1, currentBlock[1]);
      Tile* newTile = new Tile(currentBlock[0], stoi(shapeStr));
      push(newTile);
      currentBlock = "";
    }
  }
  std::string shapeStr(1, currentBlock[1]);
  Tile* newTile = new Tile(currentBlock[0], stoi(shapeStr));
  push(newTile);
}

/*
 * Method Name: getIndexOf
 * Purpose: Retrieves the index of a given tile value
 * Parameters:
 * tileString [string] - String of a tile to search for
 * Return:
 */
int LinkedList::getIndexOf(std::string tileString) {
  bool found = false;
  int index = -1;
  for (int i = 0; !found && i < size; i++) {
    if (tileString == get(i)->toString()) {
      found = true;
      index = i;
    }
  }
  return index;
}
