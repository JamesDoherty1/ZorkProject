#include "GameException.h"

GameException::GameException(const std::string& msg) : message(msg) {}

// Override the what() method to provide a custom error message
const char* GameException::what() const noexcept {
    return message.c_str();
}

