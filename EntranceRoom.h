#ifndef ZORKPROJECT_ENTRANCEROOM_H
#define ZORKPROJECT_ENTRANCEROOM_H

#include "Room.h"
#include "Player.h"
#include "StartFinish.h"

class EntranceRoom : public Room, public StartFinish{

public:
    EntranceRoom(string description, Player& player);
    bool unlocked;
    void unlockRoom();

};

#endif //ZORKPROJECT_ENTRANCEROOM_H
