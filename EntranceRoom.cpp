#include "EntranceRoom.h"
#include <iostream>

using namespace std;

EntranceRoom::EntranceRoom(string description, Player& player) : Room(description, player) {
    cout << displayMessage("starting") << endl;
}

void EntranceRoom::unlockRoom() {
    unlocked = false;

}
