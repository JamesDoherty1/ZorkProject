#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>

class Player : public Character {
public:
    Player(const std::string& name, int age, const std::string& subject);

private:
    std::string subject;
};

#endif // PLAYER_H
