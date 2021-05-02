#include <iostream>
#include <vector>
#include <string>
#include "GameState.h"
#include "LinkedList.h"
#include "TileBag.h"

GameState::GameState(Player players) {
    InitialHand(players[0].getHand());
    InitialHand(players[1].getHand());

}

GameState::~GameState(){
}

void GameState::InitialHand(LinkedList* hand) {
    for(int i =0; i < 6; ++i) {
        hand->push(TileBag().draw());
    }
}