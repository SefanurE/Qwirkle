#include <iostream>
#include <string>
#include <utility>
#include "GamePlay.h"

GamePlay::GamePlay(Board* board) {
   this->board = board;
}

GamePlay::~GamePlay(){
}

bool GamePlay::submittedTurn(Tile* tile, std::string position) {
    if(checkAdjacent(tile, position)) {
        outSuccess = true;
    }
    return outSuccess;
}

bool GamePlay::checkAdjacent(Tile* tile, std::string position) {
    int row = (int)position[0];
    int col = (int)position[1];

    std::pair<int, int> neighbours[4] = {std::make_pair(row, col - 1), std::make_pair(row - 1, col), std::make_pair(row, col + 1), std::make_pair(row + 1, col)};
    int i = 0;
    bool flag = true;
    while(flag && i < sizeof(neighbours)) {
        if (neighbours[i].second > 0 && neighbours[i].first  > 0 && neighbours[i].second < board->getWidth() && neighbours[i].first < board->getHeight()) {
            Tile* neighbourTile = board->getTile(neighbours[i].first, neighbours[i].second);
            if (neighbourTile != nullptr) {
                if (!checkPlacementValid(tile, neighbourTile)) {
                    flag = false;
                }
            }
        }
        i++;
    }
    return flag;
}

bool GamePlay::checkPlacementValid(Tile* myTile, Tile* neighbourTile) {
    bool check = false;
    if(neighbourTile->getShape() == myTile->getShape() ^ neighbourTile->getColour() == myTile->getColour()) {
        check = true;
    }
    return check;
}



