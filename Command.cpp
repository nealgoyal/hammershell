#include "Command.h"

//  protected:
//     vector<char*> commands;
//  public:

// Default Constructor
Command::Command() {

}

// Constructor: takes a vector of strings and loads the commands vector.
Command::Command(std::vector<string> input) {
    char* com = input;
    //for(int i = 0; i < input.size(); ++i) {
    //    commands.at(i) = input.at(i);
    //}
}

// Takes in a string and puts it into the vector of commands.
void Command::setComVector(std::string input) {
    //char com[] = input; 
    //char*token = strtok(com, " ")
    //commands.push_back(com);
}
