#ifndef BOXINGROOM_H_
#define BOXINGROOM_H_

#include "Room.h"
#include "Player.h"

class BoxingRoom : public Room {

public:
    BoxingRoom(string description, Player& player); // Add ZorkUL& game as a parameter

    // Override awardDescription to handle winning the game
    string awardDescription(Room* currentRoom, int location) override;

    // Override nextRoom to handle special conditions for the boxing room
    Room* nextRoom(string direction) override;
};

#endif // BOXINGROOM_H_