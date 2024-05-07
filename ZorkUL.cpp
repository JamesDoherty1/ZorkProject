#include <iostream>
#include "ZorkUL.h"

using namespace std;

int main() {
    ZorkUL game; // Create an instance of the ZorkUL game

    // Start the game
    game.play();

    return 0;
}

ZorkUL::ZorkUL() {
    createRooms();
}

void ZorkUL::createRooms()  {
    Room *entrance, *soccer, *basketball, *sprint, *swim, *chess, *tennis, *boxing, *golf;

    entrance = new Room("entrance");

    soccer = new Room("soccer");
        soccer->addItem(new Item("football", 50, "shoot"));
        soccer->addItem(new Item("cup", 25, 5));
    basketball = new Room("basketball");
        basketball->addItem(new Item("basketball", 80, "throw"));
        basketball->addItem(new Item("mvp", 10, 5));
    sprint = new Room("sprint");
        sprint->addItem(new Item("runners", 75, "sprint"));
        sprint->addItem(new Item("medal", 15, 5));
    swim = new Room("swim");
        swim->addItem(new Item("goggles", 50, "swim"));
        swim->addItem(new Item("medal", 50, 5));
    chess = new Room("chess");
        chess->addItem(new Item("king", 10, "play"));
        chess->addItem(new Item("trophy", 24, 5));
    tennis = new Room("tennis");
        tennis->addItem(new Item("racket", 60, "serve"));
        tennis->addItem(new Item("trophy", 24, 5));
    boxing = new Room("boxing");
        boxing->addItem(new Item("gloves", 30, "box"));
        boxing->addItem(new Item("belt", 1, 5));
    golf = new Room("golf");
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
    cout << "info for help" << endl;
    cout << endl;
    cout << currentRoom->equipmentDescription() << endl;
}

bool ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {
        cout << "invalid input" << endl;
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0) {
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
    } else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0) {
        if (!command.hasSecondWord()) {
            cout << "incomplete input" << endl;
        } else {
            string itemName = command.getSecondWord();
            int location = currentRoom->isItemInRoom(itemName);
            if (location < 0) {
                cout << "the item is not in the room" << endl;
            } else {
                const vector<Item>& roomItems = currentRoom->getItems();
                Item takenItem = roomItems[location];
                cout << "you have taken the " + itemName << endl;
                cout << "Item explanation: " << endl;
                cout << takenItem.getExplanation() << endl;
                cout << endl;

                // Check if the user types the correct command
                string expectedCommand = takenItem.getItemCommand();
                cout << "Enter the command '" << expectedCommand << "': ";
                string userInput;
                cin >> userInput;

                actionAttempt(userInput, expectedCommand, takenItem, location);

                currentRoom->removeItem(location);
            }
        }
    } else if (commandWord.compare("put") == 0) {
        {

        }
        /*
        {
        if (!command.hasSecondWord()) {
            cout << "incomplete input"<< endl;
            }
            else
                if (command.hasSecondWord()) {
                cout << "you're adding " + command.getSecondWord() << endl;
                itemsInRoom.push_Back;
            }
        }
    */
    } else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            cout << "overdefined input" << endl;
        else
            return true; /**signal to quit*/
    }
    return false;
}

void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();
}

void ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        cout << "incomplete input" << endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        cout << "underdefined input" << endl;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->equipmentDescription() << endl;
    }
}

string ZorkUL::go(string direction) {
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else {
        currentRoom = nextRoom;
        return currentRoom->equipmentDescription();
    }
}

void ZorkUL::actionAttempt(string userInput, string expectedCommand, Item takenItem, int location) {
    // Compare the user input with the expected command
    if (userInput == expectedCommand) {
        // Generate a random number between 1 and 100
        int randomNumber = rand() % 100 + 1;
        // Check if the random number is less than or equal to the chance of success
        if (randomNumber <= takenItem.getChance()) {
            cout << "Well done! You successfully completed the action." << endl;
            cout << currentRoom->awardDescription() << endl;
            currentRoom->removeItem(location);
        } else {
            cout << "You failed to complete the action.Try again!" << endl;
            string expectedCommand = takenItem.getItemCommand();
            cout << "Enter the command '" << expectedCommand << "': ";
            string userInput;
            cin >> userInput;
            actionAttempt(userInput, expectedCommand, takenItem, location);
        }
    } else {
        cout << "Incorrect command. Try again." << endl;
    }
}

void ZorkUL::play() {
    printWelcome();

    bool finished = false;
    while (!finished) {
        Command* command = parser.getCommand();
        finished = processCommand(*command);
        delete command;
    }
    cout << endl;
    cout << "end" << endl;
}
