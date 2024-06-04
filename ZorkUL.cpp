#include "ZorkUL.h"
#include "BoxingRoom.h"
#include "GameException.h"

using namespace std;

ZorkUL::ZorkUL() : player("PlayerName", 20, "PlayerSubject"), takenItem("Default Item", 0, 0), location(0) {
    createRooms();
    printWelcome();
}

void ZorkUL::createRooms() {
    Room *entrance, *soccer, *basketball, *sprint, *swim, *chess, *tennis, *boxing, *golf;

    entrance = new Room("entrance", player, *this);
    entrance->addItem(new Item("key", 50, "open"));
    entrance->addItem(new Item("water", 25, 5));
    soccer = new Room("soccer", player, *this);
    soccer->addItem(new Item("football", 50, "shoot"));
    soccer->addItem(new Item("cup", 25, 5));
    basketball = new Room("basketball", player, *this);
    basketball->addItem(new Item("basketball", 80, "throw"));
    basketball->addItem(new Item("mvp", 10, 5));
    sprint = new Room("sprint", player, *this);
    sprint->addItem(new Item("runners", 75, "sprint"));
    sprint->addItem(new Item("medal", 15, 5));
    swim = new Room("swim", player, *this);
    swim->addItem(new Item("goggles", 50, "swim"));
    swim->addItem(new Item("medal", 50, 5));
    chess = new Room("chess", player, *this);
    chess->addItem(new Item("king", 10, "play"));
    chess->addItem(new Item("trophy", 24, 5));
    tennis = new Room("tennis", player, *this);
    tennis->addItem(new Item("racket", 60, "serve"));
    tennis->addItem(new Item("trophy", 24, 5));
    boxing = new BoxingRoom("boxing", player, *this);
    boxing->addItem(new Item("gloves", 30, "box"));
    boxing->addItem(new Item("belt", 1, 5));
    golf = new Room("golf", player, *this);
    golf->addItem(new Item("club", 1, "swing"));
    golf->addItem(new Item("voucher", 99, 5));

    //             (N, E, S, W)
    entrance->setExits(NULL, soccer, golf, basketball);
    soccer->setExits(swim, NULL, NULL, entrance);
    basketball->setExits(sprint, entrance, NULL, NULL);
    sprint->setExits(swim, NULL, basketball, NULL);
    swim->setExits(NULL, tennis, soccer, chess);
    chess->setExits(boxing, swim, NULL, NULL);
    tennis->setExits(boxing, NULL, NULL, swim);
    boxing->setExits(golf, NULL, chess, NULL);
    golf->setExits(entrance, NULL, boxing, NULL);

    currentRoom = entrance;
}

void ZorkUL::printWelcome() {
    cout << "start" << endl;
    cout << "Work through the arena and beat Mike Tyson to Win!" << endl;
    GUIPrint("entrance", "image");
    cout << currentRoom->shortDescription() << endl;
    cout << currentRoom->equipmentDescription() << endl;

    GUIPrint("Work through the arena and beat Mike Tyson to Win!", "top");
    GUIPrint(currentRoom->equipmentDescription(), "second");
}

bool ZorkUL::processCommand(Command command) {
    try {
        if (command.isUnknown()) {
            throw GameException("Invalid input");
        }
    } catch (const GameException& ex) {
        cerr << "Game Exception: " << ex.what() << endl;
    } catch (const exception& ex) {
        cerr << "Standard Exception: " << ex.what() << endl;
    } catch (...) {
        cerr << "Unknown Exception occurred" << endl;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0) {
        printHelp();
    }
    else if (commandWord.compare("go") == 0) {
        goRoom(command);
    }
    else if (commandWord.compare("take") == 0) {
        if (!command.hasSecondWord()) {
            throw GameException("incomplete input");
        }
        else {
            string itemName = command.getSecondWord();
            location = currentRoom->isItemInRoom(itemName);
            if (location < 0) {
                cout << "the item is not in the room" << endl;
                GUIPrint("the item is not in the room", "second");
            } else {
                takeItem(itemName);
            }
        }
    }
    else if (commandWord.compare(equipmentAction) == 0) {
        if (!currentRoom->isEmpty()) {
            performAction();
        }
        else {
            cout << "Incorrect command. Try again." << endl;
            GUIPrint("Incorrect command. Try again.", "first");
        }
    }
    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord()) {
            throw GameException("overdefined input");
        } else {
            return true;
        }
    }
    return false;
}

void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();
}

void ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        throw GameException("Incomplete input");
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL) {
        cout << "You've hit a wall!" << endl;
        GUIPrint("You've hit a wall!", "general");

    } else if (nextRoom->shortDescription() == "boxing") {
        if (std::stoi(player.getStrength()) < 99) {
            player.clearStrong();
            cout << "Get stronger!" << endl;
            GUIPrint("Get stronger!", "first");
            cout << currentRoom->exitString() << endl;
            GUIPrint(currentRoom->exitString(), "second");
        } else {
            player.setStrong();
            if (player.isPlayerStrong()) {
                GUIPrint("boxing", "image");
                currentRoom = nextRoom;
                cout << currentRoom->equipmentDescription() << endl;
                GUIPrint(currentRoom->equipmentDescription(), "second");
            }
        }
    } else {
        currentRoom = nextRoom;
        GUIPrint(currentRoom->shortDescription(), "image");
        cout << currentRoom->equipmentDescription() << endl;
        GUIPrint(currentRoom->equipmentDescription(), "second");
    }
}

string ZorkUL::go(string direction) {
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return ("direction null");
    else {
        currentRoom = nextRoom;
        return currentRoom->equipmentDescription();
    }
}

bool ZorkUL::update(const std::string& userInput) {
    Command* command = parser.getCommand(userInput);
    bool finished = processCommand(*command);
    delete command;
    return finished;
}

void ZorkUL::GUIPrint(string message, string type) {
    QString GUIMessage = QString::fromStdString(message);
    if (type == "second") {
        emit secondMessage(GUIMessage);
    }
    else if (type == "top") {
        emit topMessage(GUIMessage);
    }
    else if (type == "score") {
        emit scoreMessage(GUIMessage);
    }
    else if (type == "image") {
        emit setImage(GUIMessage);
    }
    else {
        emit firstMessage(GUIMessage);
    }
}

void ZorkUL::takeItem(string itemName) {
    const vector<Item>& roomItems = currentRoom->getItems();
    takenItem = roomItems[location];
    cout << "you have taken the " + itemName << endl;
    GUIPrint("you have taken the " + itemName, "second");
    if(takenItem.getIsAward()){
        GUIPrint(("You have taken the " + takenItem.getShortDescription()), "first");
        GUIPrint(currentRoom->exitString(), "second");
    }
    currentRoom->removeItem(location);
    if (!currentRoom->isEmpty()) {
        cout << "Item explanation: " << endl;
        cout << takenItem.getExplanation() << endl;
        GUIPrint("Item explanation: ", "first");
        GUIPrint(takenItem.getExplanation(), "second");

        equipmentAction = takenItem.getItemCommand();
    }
}
void ZorkUL :: performAction(){
    int randomNumber = rand() % 100 + 1;
    if (randomNumber <= takenItem.getChance()) {
        currentRoom->awardDescription(currentRoom, location);
    }
    else {
        cout << "You failed to complete the action. Try again!" << endl;
        GUIPrint("You failed to complete the action. Try again!", "first");
    }
}


void ZorkUL::closeWindow() {
    emit closeGameWindow();
}

string ZorkUL :: getCurrentItem(){
    const vector<Item>& roomItems = currentRoom->getItems();
    takenItem = roomItems[location];
    return takenItem.getShortDescription();
}
