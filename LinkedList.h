#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
  public:
    LinkedList();
    ~LinkedList();
    int getSize();
    void push(Tile* tile);
    Tile* pop();
    void insertAfter(int index, Tile* tile);
    Tile* remove(int index);
    Tile* get(int index);
    std::string toString();
    std::string toStringColour();
    void fromString(std::string listString);
    int getIndexOf(std::string tileString);

  private:
    Node* head;
    Node* tail;
    int size;

    Node* getNode(int index);
};

#endif // ASSIGN2_LINKEDLIST_H
