#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "item.h"
#include "Player.h"
#include "Attribute.h"

using namespace std;

class Room {

private:
    string description;
    map<string, Room*> exits;
    Player& player;

protected:
    vector<Item> itemsInRoom;
public:
    Room(string description, Player& player);
    Room(const Room& other);
    virtual ~Room() = default; // Virtual destructor for polymorphic behavior

    virtual void setExits(Room *north, Room *east, Room *south, Room *west);
    virtual string shortDescription();
    virtual string equipmentDescription();
    virtual string awardDescription(Room* currentRoom, int location);
    virtual string exitString();
    virtual Room* nextRoom(string direction);
    virtual void addItem(Item *inItem);
    virtual int isItemInRoom(string inString);
    virtual bool isEmpty() const;
    virtual const vector<Item>& getItems() const;
    virtual void removeItem(int index);
};

#endif // ROOM_H_