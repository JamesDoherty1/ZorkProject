#ifndef ZORKUL_H_
#define ZORKUL_H_

#include <iostream>
#include "Room.h"
#include "Command.h"
#include "Parser.h"

using namespace std;

class ZorkUL {
private:
    Room *currentRoom;
    Parser parser; // Add Parser object as a member variable

public:
    ZorkUL();
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    string go(string direction);
    void actionAttempt(string userInput, string expectedCommand, Item takenItem, int location);
    void play();
};

#endif /*ZORKUL_H_*/
