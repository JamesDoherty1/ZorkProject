#include "BoxingRoom.h"
#include <iostream>

using namespace std;

BoxingRoom::BoxingRoom(string description, Player& player) : Room(description, player) {
}

string BoxingRoom::awardDescription(Room* currentRoom, int location) {
    for (const Item &item: itemsInRoom) {
        if (item.getIsAward()) {
            cout << displayMessage("finished") << endl;
            cout << "Type 'quit' to end game" << endl;
        }
    }
    return ""; // Ensure a return value for all paths
}


Room* BoxingRoom::nextRoom(string direction) {
    if (direction == "west") {
        cout << "Get stronger!" << endl;
        return nullptr;
    }
    return Room::nextRoom(direction);
}
