#include "BoxingRoom.h" // Include the header file for BoxingRoom
#include <iostream> // Include necessary headers here

using namespace std;

BoxingRoom::BoxingRoom(string description, Player& player) : Room(description, player) {
    // Add any specific initialization if needed
}

string BoxingRoom::awardDescription(Room* currentRoom, int location) {
    cout << "Congratulations! You have won the game by taking the belt." << endl;
    return "Congratulations! You have won the game by taking the belt.";
}

Room* BoxingRoom::nextRoom(string direction) {
    if (direction == "west") {
        cout << "Get stronger!" << endl;
        return nullptr;
    }
    return Room::nextRoom(direction);
}
