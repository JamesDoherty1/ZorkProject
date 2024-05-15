#include "Player.h"

Player::Player(const string& name, int age, const string& subject)
        : totalExperience(0), totalStrength(0) {
}

Player::Player(const Player& other)
        : subject(other.subject), totalExperience(other.totalExperience), totalStrength(other.totalStrength) {}

void Player::addExperience(string experience) {
    totalExperience += std::stoi(experience);
}

void Player::addStrength(string strength) {
    totalStrength += std::stoi(strength);
}

string Player::getExperience() {
    return std::to_string(totalExperience.getValue());
}

string Player::getStrength() {
    return std::to_string(totalStrength.getValue());
}