#include "StartFinish.h"
#include <iostream>

string StartFinish::displayMessage(string startFinish) {
    startFinishMessage = "You are " + startFinish + " the game"; // Assign value
    return startFinishMessage;
}