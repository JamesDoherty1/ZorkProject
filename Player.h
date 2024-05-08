#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
    Player(const string& name, int age, const string& subject);
    void addExperience(string experience);
    void addStrength(string strength);
    string getExperience ();
    string getStrength();

private:
    std::string subject;
    int totalExperience;
    int totalStrength;

};

#endif // PLAYER_H
