#include "Room.h"
#include "ZorkUL.h"

Room::Room(string description, Player& player, ZorkUL& zorkUL)
    : description(description), player(player), zorkUL(zorkUL) {
}

Room::Room(const Room& other)
    : description(other.description), exits(other.exits), player(other.player), itemsInRoom(other.itemsInRoom), zorkUL(other.zorkUL) {
}

void Room::setExits(Room* north, Room* east, Room* south, Room* west) {
    if (north != nullptr) exits["north"] = north;
    if (east != nullptr) exits["east"] = east;
    if (south != nullptr) exits["south"] = south;
    if (west != nullptr) exits["west"] = west;
}

string Room::shortDescription() {
    return description;
}

string Room::equipmentDescription() {
    stringstream descriptionStream;
    zorkUL.GUIPrint("", "first");
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

string Room::awardDescription(Room* currentRoom, int location) {
    if (!itemsInRoom.empty() && currentRoom->shortDescription() != "entrance") {
        zorkUL.GUIPrint("Well done, You have won the following items:", "first");
        for (const Item& item : itemsInRoom) {
            if (item.getIsAward()) {
                player.addExperience(std::to_string(item.getAwardExperience().getValue()));
                player.addStrength(std::to_string(item.getAwardStrength().getValue()));
                zorkUL.GUIPrint("Total Experience: " + player.getExperience() + "  Total Strength: " + player.getStrength(), "score");
                zorkUL.GUIPrint(item.getShortDescription(), "second");
            }

        }
    }
    else if(currentRoom->shortDescription() == "entrance"){
        zorkUL.GUIPrint("Well done, You have opened the door", "first");
        zorkUL.GUIPrint(currentRoom->exitString(), "second");
    }
    return "";
}

string Room::exitString() {
    string returnString = "Exits: ";
    for (auto const& [direction, room] : exits) {
        returnString += direction + " ";
    }
    return returnString;
}

Room* Room::nextRoom(string direction) {
    if (exits.find(direction) != exits.end()) {
        return exits[direction];
    }
    return nullptr;
}

void Room::addItem(Item* inItem) {
    itemsInRoom.push_back(*inItem);
}

int Room::isItemInRoom(string inString) {
    for (size_t i = 0; i < itemsInRoom.size(); ++i) {
        if (itemsInRoom[i].getShortDescription() == inString) {
            return i;
        }
    }
    return -1;
}

bool Room::isEmpty() const {
    return itemsInRoom.empty();
}

const vector<Item>& Room::getItems() const {
    return itemsInRoom;
}

void Room::removeItem(int index) {
    if (index >= 0 && index < itemsInRoom.size()) {
        itemsInRoom.erase(itemsInRoom.begin() + index);
    }
}



