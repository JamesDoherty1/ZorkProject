#include "item.h"

Item::Item(string inDescription, int inStrength, int inExperience) {
    description = inDescription;
    awardStrength = Attribute<int>(inStrength); // Initialize with provided strength
    awardExperience = Attribute<int>(inExperience); // Initialize with provided experience
    isAward = true;
}

Item::Item(string inDescription, int inChance, string inItemCommand) {
    description = inDescription;
    chance = inChance;
    itemCommand = inItemCommand;
    isAward = false;
}

Item::Item(const Item& other)
        : description(other.description), itemCommand(other.itemCommand),
          awardStrength(other.awardStrength), awardExperience(other.awardExperience),
          chance(other.chance), isAward(other.isAward) {}

void Item::setStrength(int inStrength) {
    if (inStrength > 9999 || inStrength < 0)
        cout << "strength invalid, must be 0<strength<9999";
    else
        awardStrength = inStrength;
}

void Item::setExperience(int inExperience) {
    if (inExperience > 9999 || inExperience < 0)
        cout << "experience invalid, must be 0<experience<9999";
    else
        awardExperience = inExperience;
}

string Item::getShortDescription() const {
    return description;
}

string Item::getLongDescription() {
    return " item(s), " + description + ".\n";
}

string Item::getExplanation() const{
    return "Type '" + itemCommand + "' : You have a " + std::to_string(chance) + "% chance to win";
}

bool Item::getIsAward() const {
    return isAward;
}

int Item::getChance() {
    return chance;
}
string Item::getItemCommand(){
    return itemCommand;
}

const Attribute<int> Item::getAwardStrength() const {
    return awardStrength;
}

const Attribute<int> Item::getAwardExperience() const {
    return awardExperience;
}