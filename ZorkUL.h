#ifndef ZORKUL_H
#define ZORKUL_H

#include <QObject>
#include "Room.h"
#include "Item.h"
#include "Command.h"
#include "Parser.h"
#include "Player.h"

class Room;

class ZorkUL : public QObject {
    Q_OBJECT

public:
    ZorkUL();
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void GUIPrint(string message, string type);
    string go(string direction);
    bool update(const string& userInput);
    void takeItem (string itemName);
    void performAction ();
    string getCurrentItem();

signals:
    void requestUserInput(const QString& prompt);
    void closeGameWindow();
    void setImage(const QString& prompt);
    void takeButton(const QString& prompt);
    void actionButton(const QString& prompt);
    void secondMessage(const QString& message);
    void firstMessage(const QString& message);
    void topMessage(const QString& message);
    void scoreMessage(const QString& message);

public slots:
    void closeWindow();

private:
    Room* currentRoom;
    Parser parser;
    Player player;
    Item takenItem;
    std::string equipmentAction;
    int location;
};

#endif // ZORKUL_H
