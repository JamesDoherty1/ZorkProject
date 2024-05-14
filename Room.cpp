#include "Room.h"

Room::Room(string description, Player& player) : description(description), player(player) {}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != nullptr)
        exits["north"] = north;
    if (east != nullptr)
        exits["east"] = east;
    if (south != nullptr)
        exits["south"] = south;
    if (west != nullptr)
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
            if(!item.getIsAward()) {
                description += "- " + item.getShortDescription() + "\n";
            }
        }
    }
    return description;
}

string Room::awardDescription(Room* currentRoom, int location) {
    string description;
    if (!itemsInRoom.empty() && currentRoom->shortDescription() != "entrance") {
        cout << "You have won the following items:" << endl;
        for (const Item &item: itemsInRoom) {
            if (item.getIsAward()) {
                cout << item.getShortDescription() << endl;
                cout << "You have gained " + to_string(item.getAwardExperience().getValue()) + " Experience, and " +
                        to_string(item.getAwardStrength().getValue()) + " Strength" << endl;

                player.addExperience(std::to_string(item.getAwardExperience().getValue()));
                player.addStrength(std::to_string(item.getAwardStrength().getValue()));

                cout<< "Total Experience: " + player.getExperience() << endl;
                cout<< "Total Strength: " + player.getStrength() << endl;

            }
        }
    }
    else if(currentRoom->shortDescription() == "entrance"){
        cout << "Go to a new room" << endl;
        cout << currentRoom->exitString() << endl;
    }
    return description;
}

string Room::exitString() {
    string returnString = "exits =";
    for (const auto& exit : exits)
        returnString += "  " + exit.first;
    return returnString;
}

Room* Room::nextRoom(string direction) {
    auto next = exits.find(direction);
    if (next == exits.end())
        return nullptr;
    return next->second;
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

int Room::isItemInRoom(string inString) {
    for (int i = 0; i < itemsInRoom.size(); ++i) {
        if (inString == itemsInRoom[i].getShortDescription())
            return i;
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
    itemsInRoom.erase(itemsInRoom.begin() + index);
}