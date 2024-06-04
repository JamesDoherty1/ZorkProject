#ifndef ROOM_H_
#define ROOM_H_

#include <QObject>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Player.h"

class ZorkUL;


class Room : public QObject {
    Q_OBJECT

private:
    string description;
    map<string, Room*> exits;
    Player& player;

protected:
    vector<Item> itemsInRoom;
    ZorkUL& zorkUL;

public:
    Room(string description, Player& player, ZorkUL& zorkUL);
    Room(const Room& other);
    virtual ~Room() = default;

    void setExits(Room* north, Room* east, Room* south, Room* west);
    string shortDescription();
    string equipmentDescription();
    virtual string awardDescription(Room* currentRoom, int location);
    string exitString();
    virtual Room* nextRoom(string direction);
    void addItem(Item* inItem);
    int isItemInRoom(string inString);
    bool isEmpty() const;
    const vector<Item>& getItems() const;
    void removeItem(int index);
    void GUIPrint(const string& message);
signals:
    void generalMessage(const QString& message);
    void roomMessage(const QString& message);
    void topMessage(const QString& message);
    void scoreMessage(const QString& message);
};

#endif // ROOM_H_
