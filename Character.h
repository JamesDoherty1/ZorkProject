#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    Character(const std::string& name, int age);
    // Other member functions and data members...
private:
    std::string name;
    int age;
};

#endif // CHARACTER_H
