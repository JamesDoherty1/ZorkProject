#ifndef ZORKPROJECT_GAMEEXCEPTION_H
#define ZORKPROJECT_GAMEEXCEPTION_H


#include <exception>
#include <string>

class GameException : public std::exception {
private:
    std::string message;
public:
    GameException(const std::string& msg);

    const char* what() const noexcept override;
};

#endif //ZORKPROJECT_GAMEEXCEPTION_H

