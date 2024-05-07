#include "Player.h"

Player::Player(const std::string& name, int age, const std::string& subject)
        : totalExperience(0), totalStrength(0) {
    // Constructor implementation
}

void Player::addExperience(std::string experience) {
    totalExperience += std::stoi(experience);
}

void Player::addStrength(std::string strength) {
    totalStrength += std::stoi(strength);
}

std::string Player::getExperience() {
    return std::to_string(totalExperience);
}

std::string Player::getStrength() {
    return std::to_string(totalStrength);
}
