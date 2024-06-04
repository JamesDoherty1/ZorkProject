#include "BoxingRoom.h"
#include <iostream>
#include <QTimer>

BoxingRoom::BoxingRoom(string description, Player& player, ZorkUL& zorkUL)
    : Room(description, player, zorkUL) {
}

string BoxingRoom::awardDescription(Room* currentRoom, int location) {
    for (const Item &item : itemsInRoom) {
        if (item.getIsAward()) {
            cout << "finished" << endl;
            zorkUL.GUIPrint("You have completed the game!", "first");
            zorkUL.GUIPrint("Winner winner chicken dinner!", "top");
            zorkUL.GUIPrint("Congratulations!!!", "second");

            QTimer::singleShot(5000, &zorkUL, &ZorkUL::closeWindow);
        }
    }
    return "";
}

Room* BoxingRoom::nextRoom(string direction) {
    if (direction == "west") {
        cout << "Get stronger!" << endl;
        return nullptr;
    }
    return Room::nextRoom(direction);
}

