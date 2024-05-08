#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "item.h"
#include "Player.h"

using namespace std;
using std::vector;

class Room {

private:
    string description;
    string taskDescription;
    int successPercentage;
    map<string, Room*> exits;
    vector<Item> itemsInRoom;
    Player& player;

public:
    Room(string description, Player& player);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    string shortDescription();
    string equipmentDescription();
    string awardDescription();
    string exitString();
    stringstream descriptionStream;
    Room* nextRoom(string direction);
    void addItem(Item *inItem);
    int isItemInRoom(string inString);
    bool performTask();
    const vector<Item>& getItems() const;

    void removeItem(int index);
};

#endif
