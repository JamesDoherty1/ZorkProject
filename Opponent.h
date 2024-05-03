#ifndef OPPONENT_H
#define OPPONENT_H

#include "Character.h"
#include <string>

class Opponent : public Character {
public:
    Opponent(const std::string& name, int age, const std::string& role);

private:
    std::string role;
};

#endif // OPPONENT_H
