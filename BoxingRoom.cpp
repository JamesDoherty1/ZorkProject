#include "BoxingRoom.h"
#include <iostream>

using namespace std;

BoxingRoom::BoxingRoom(string description, Player& player) : Room(description, player) {
    // Add any specific initialization if needed
}

string BoxingRoom::awardDescription(Room* currentRoom, int location) {
    for (const Item &item: itemsInRoom) {
        if (item.getIsAward()) {
            cout << "You are the Champion!!!" << endl;
            cout << "Type 'quit' to end game" << endl;
            string userInput;
            cin >> userInput;
            if(userInput == "quit") {
                cout<< "Congratulations! You have won the game!" << endl;
            }
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