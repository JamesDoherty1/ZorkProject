#include "GameException.h"

GameException::GameException(const std::string& msg) : message(msg) {}

const char* GameException::what() const noexcept {
    return message.c_str();
}


