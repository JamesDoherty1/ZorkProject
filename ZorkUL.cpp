#include <iostream>
#include "ZorkUL.h"
#include "BoxingRoom.h"

using namespace std;

int main() {
    ZorkUL game; // Create an instance of the ZorkUL game

    // Start the game
    game.play();

    return 0;
}

ZorkUL::ZorkUL() : player("PlayerName", 20, "PlayerSubject") {
    createRooms();
}

void ZorkUL::createRooms()  {
    Room *entrance, *soccer, *basketball, *sprint, *swim, *chess, *tennis, *boxing, *golf;

    entrance = new Room("entrance", player);

    soccer = new Room("soccer", player);
        soccer->addItem(new Item("football", 50, "shoot"));
        soccer->addItem(new Item("cup", 25, 5));
    basketball = new Room("basketball", player);
        basketball->addItem(new Item("basketball", 80, "throw"));
        basketball->addItem(new Item("mvp", 10, 5));
    sprint = new Room("sprint", player);
        sprint->addItem(new Item("runners", 75, "sprint"));
        sprint->addItem(new Item("medal", 15, 5));
    swim = new Room("swim", player);
        swim->addItem(new Item("goggles", 50, "swim"));
        swim->addItem(new Item("medal", 50, 5));
    chess = new Room("chess", player);
        chess->addItem(new Item("king", 10, "play"));
        chess->addItem(new Item("trophy", 24, 5));
    tennis = new Room("tennis", player);
        tennis->addItem(new Item("racket", 60, "serve"));
        tennis->addItem(new Item("trophy", 24, 5));
    boxing = new BoxingRoom("boxing", player);
        boxing->addItem(new Item("gloves", 30, "box"));
        boxing->addItem(new Item("belt", 1, 5));
    golf = new Room("golf", player);
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
    cout << "Work through the arena and beat Mike Tyson to Win!";
    cout << "To enter the boxing room you are required to have 99 Strength";
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
    }

    else if (commandWord.compare("go") == 0)
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
                currentRoom->removeItem(location);
                if (itemName == "belt") {
                    cout << "Congratulations! You have won the game by taking the belt." << endl;
                    return true; // Signal to quit the game
                } else {
                    if (!currentRoom->isEmpty()) {
                        cout << "Item explanation: " << endl;
                        cout << takenItem.getExplanation() << endl;
                        cout << endl;

                        // Check if the user types the correct command
                        string expectedCommand = takenItem.getItemCommand();
                        cout << "Enter the command '" << expectedCommand << "': ";
                        string userInput;
                        cin >> userInput;

                        actionAttempt(userInput, expectedCommand, takenItem, location);
                    } else {
                        cout << "Go to a new room" << endl;
                        cout << currentRoom->exitString() << endl;
                    }
                }
            }
        }

} else if (commandWord.compare("put") == 0) {
        /*{
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

    if (nextRoom == NULL) {
        cout << "underdefined input" << endl;
    }
    else if(nextRoom->shortDescription() == "boxing"){
        if (std::stoi(player.getStrength()) < 99){
            cout<< "Get stronger!" << endl;
            cout<< currentRoom->exitString() <<endl;
        }
        else{
            currentRoom = nextRoom;
            cout << currentRoom->equipmentDescription() << endl;
        }
    }
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

    if (!currentRoom->isEmpty()) {
            if (userInput == expectedCommand) {
                int randomNumber = rand() % 100 + 1;
                if (randomNumber <= takenItem.getChance()) {
                    cout << "Well done! You successfully completed the action." << endl;
                    cout << currentRoom->awardDescription(currentRoom, location) << endl;
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
                string expectedCommand = takenItem.getItemCommand();
                cout << "Enter the command '" << expectedCommand << "': ";
                string userInput;
                cin >> userInput;
                actionAttempt(userInput, expectedCommand, takenItem, location);
            }
        }

    else {
            cout << "Go to a new room" << endl;
            cout << currentRoom->exitString();
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