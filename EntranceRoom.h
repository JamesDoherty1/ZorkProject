#ifndef ZORKPROJECT_ENTRANCEROOM_H
#define ZORKPROJECT_ENTRANCEROOM_H

#include "Room.h"
#include "Player.h"
#include "StartFinish.h"
#include "ZorkUL.h"

class EntranceRoom : public Room, public StartFinish {

public:
    EntranceRoom(std::string description, Player& player, ZorkUL& zorkUL);
    bool unlocked;
    void unlockRoom();

};

#endif // ZORKPROJECT_ENTRANCEROOM_H

