#include "EntranceRoom.h"
#include <iostream>

EntranceRoom::EntranceRoom(std::string description, Player& player, ZorkUL& zorkUL)
    : Room(description, player, zorkUL) {
    unlocked = false;
}

void EntranceRoom::unlockRoom() {
    unlocked = true;
}


