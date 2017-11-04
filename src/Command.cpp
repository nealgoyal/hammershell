#include "Command.h"
#include <iostream>
#include <vector>

//  protected:
//     vector<char*> commands;
//  public:

// Constructor: takes a vector of char* and loads the commands vector.
Command::Command(std::vector<char*> input) {
    // commands = input;
}

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(char* input) {
    char delim[] = "|&;";
    //cout << "The tokens are:" << endl;
    char *token = strtok(input,delim);
    commands.push_back(token);
}

// Displays all of the contents of the vector of commands.
void Command::display() {
    for(int i = 0; i < commands.size(); ++i) {
        std::cout << commands.at(i) << std::endl;
    }

    std::cout << commands.at(0) << std::endl;
    std::cout << commands.at(1) << std::endl;
    std::cout << commands.at(2) << std::endl;

}
