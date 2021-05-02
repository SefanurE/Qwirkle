#include <iostream>
#include <vector>
#include <string>
#include "GameState.h"

GameState::GameState(Player players) {
    players[0]->hand = InitialHand();
    players[1]->hand = InitialHand();

}

GameState::~GameState(){
}

void GameState::InitialHand() {
    for(int i =0; i < 6; ++i) {
        
    }
}