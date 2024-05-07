#include "Room.h"
#include <cstdlib>

Room::Room(string description) {
    this->description = description;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
}

string Room::shortDescription() {
    return description;
}

string Room::equipmentDescription() {
    stringstream descriptionStream;
    descriptionStream << "room = " << description << ".\n" << exitString();
    string description = descriptionStream.str();
    description += "\n";
    if (!itemsInRoom.empty()) {
        description += "Items in room:\n";
        for (const Item& item : itemsInRoom) {
            if (!item.getIsAward()) {
                description += "- " + item.getShortDescription() + "\n";
            }
        }
    }
    return description;
}
string Room::awardDescription() {
    string description;
    if (!itemsInRoom.empty()) {
        cout << "You have won the following items:" << endl;
        for (const Item &item: itemsInRoom) {
            if (item.getIsAward()) {
                cout << item.getShortDescription() << endl;
                cout << "You have gained " + to_string(item.getAwardExperience()) + " Experience, and " +
                        to_string(item.getAwardStrength()) + " Strength" << endl;

                player.addExperience(item.getAwardExperience());
                player.addStrength(item.getAwardStrength());
            }
        }
    }
    return description;
}


string Room::exitString() {
    string returnString = "exits =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        returnString += "  " + i->first;
    return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction);
    if (next == exits.end())
        return NULL;
    return next->second;
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

int Room::isItemInRoom(string inString) {
    int sizeItems = itemsInRoom.size();
    if (sizeItems < 1) {
        return -1;
    } else {
        for (int x = 0; x < sizeItems; x++) {
            int tempFlag = inString.compare(itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                return x;
            }
        }
    }
    return -1;
}

bool Room::performTask() {
    int randomNumber = rand() % 100 + 1;
    if (randomNumber <= successPercentage) {
        return true;
    } else {
        return false;
    }
}

const vector<Item>& Room::getItems() const {
    return itemsInRoom;
}

void Room::removeItem(int index) {
    itemsInRoom.erase(itemsInRoom.begin() + index);
}
