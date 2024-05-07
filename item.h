#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    string description;
    string itemCommand;
    int awardStrength;
    int awardExperience;
    int chance;
    bool isAward;

public:
    Item(string inDescription, int inStrength, int inExperience);
    Item(string inDescription, int inChance, string inItemCommand);
    void setStrength(int inStrength);
    void setExperience(int inExperience);
    string getShortDescription() const;
    string getLongDescription();
    string getExplanation() const;
    string getItemCommand();
    bool getIsAward() const;
    int getChance();
    int getAwardStrength()const;
    int getAwardExperience()const;
};

#endif /*ITEM_H_*/
