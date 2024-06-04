#include "CommandWords.h"


vector<string> CommandWords::validCommands;

CommandWords::CommandWords() {
    if (validCommands.empty()) {
        validCommands.push_back("go");
        validCommands.push_back("quit");
        validCommands.push_back("info");
        validCommands.push_back("map");
        validCommands.push_back("take");
        validCommands.push_back("put");
        validCommands.push_back("open");
        validCommands.push_back("shoot");
        validCommands.push_back("throw");
        validCommands.push_back("sprint");
        validCommands.push_back("swim");
        validCommands.push_back("play");
        validCommands.push_back("serve");
        validCommands.push_back("box");
        validCommands.push_back("swing");
    }
}

bool CommandWords::isCommand(string aString) {
    for (unsigned int i = 0; i < validCommands.size(); i++) {
        if (validCommands[i].compare(aString) == 0)
            return true;
    }
    return false;
}

void CommandWords::showAll() {
    for (unsigned int i = 0; i < validCommands.size(); i++) {
        cout << validCommands[i] << "  ";
    }
    cout << endl;
}
