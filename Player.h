#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Attribute.h"

using namespace std;

// Bit structure to represent player's strength status
struct StrengthStatus {
    unsigned int isStrong : 1;
};

class Player {
public:
    Player(const string& name, int age, const string& subject);
    Player(const Player& other);
    void addExperience(string experience);
    void addStrength(string strength);
    string getExperience ();
    string getStrength();
    void setStrong();
    void clearStrong();
    bool isPlayerStrong() const;
    virtual ~Player() {}

private:
    std::string subject;
    Attribute<int> totalExperience;
    Attribute<int> totalStrength;
    StrengthStatus strengthStatus; // Bit field to represent strength status
};

#endif // PLAYER_H
