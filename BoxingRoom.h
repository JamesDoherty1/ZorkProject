#ifndef BOXINGROOM_H_
#define BOXINGROOM_H_

#include "Room.h"
#include "Player.h"
#include "StartFinish.h"
#include "ZorkUL.h"
#include <QTimer>

class BoxingRoom : public Room, public StartFinish {
    Q_OBJECT

public:
    BoxingRoom(std::string description, Player& player, ZorkUL& zorkUL);

    std::string awardDescription(Room* currentRoom, int location) override;
    Room* nextRoom(std::string direction) override;
};

#endif // BOXINGROOM_H_

