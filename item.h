#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
#include "Attribute.h"
using namespace std;

class Item {
private:
    string description;
    string itemCommand;
    Attribute<int> awardStrength;
    Attribute<int> awardExperience;
    int chance;
    bool isAward;

public:
    Item(string inDescription, int inStrength, int inExperience);
    Item(string inDescription, int inChance, string inItemCommand);
    Item(const Item& other);
    void updateStats(string description);
    void setStrength(int inStrength);
    void setExperience(int inExperience);
    string getShortDescription() const;
    string getLongDescription();
    string getExplanation() const;
    string getItemCommand();
    bool getIsAward() const;
    int getChance();
    const Attribute<int> getAwardStrength()const;
    const Attribute<int> getAwardExperience()const;
};

#endif /*ITEM_H_*/