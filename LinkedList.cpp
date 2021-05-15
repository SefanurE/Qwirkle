#include "LinkedList.h"
#include <iostream>


LinkedList::LinkedList() {
   head = nullptr;
   size = 0;
}

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

void LinkedList::push(Tile *tile) {
  Node* newNode = new Node(tile, nullptr);
  if (size == 0) {
    head = newNode;
  } else {
    Node* endNode = getNode(size - 1);
    endNode->next = newNode;
  }
  size++;
}

Tile* LinkedList::pop() {
  return remove(0);;
}

void LinkedList::insertAfter(int index, Tile *tile) {
  if (index < size) {
    Node* nextNode = getNode(index + 1);
    Node* newNode = new Node(tile, nextNode);
    getNode(index)->next = newNode;
  } else {
    getNode(index)->next = new Node(tile, nullptr);
  }
  size++;
}

Tile* LinkedList::remove(int index) {
  Node* removeNode = getNode(index);
  if (index == 0) {
    head = removeNode->next;
  } else {
    getNode(index - 1)->next = removeNode->next;
  }
  size--;
  Tile* removeTile = removeNode->tile;
  delete removeNode;
  return removeTile;
}

Tile* LinkedList::get(int index) {
  return getNode(index)->tile;
}

Node* LinkedList::getNode(int index) {
  Node* retrieveNode = head;
  for (int i = 0; i < index; i++) {
    retrieveNode = retrieveNode->next;
  }
  return retrieveNode;
}

std::string LinkedList::toString() {
  std::string listString = "";
  Node* node = head;
  while (node != nullptr) {
    listString += node->tile->toString();
    if (node->next != nullptr) {
      listString += ",";
    }
    node = node->next;
  }
  return listString;
}

int LinkedList::getSize() {
  return size;
}

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
