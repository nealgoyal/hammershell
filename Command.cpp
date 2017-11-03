#include "Command.h"

//  protected:
//     vector<char*> commands;
//  public:

// Constructor: takes a vector of char* and loads the commands vector.
Command::Command(std::vector<char*> input) {
    commands = input;
}

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(char* input) {
    commands.push_back(input);
    // Below is if it input is string; not finished.
    // char com[] = input;
    // char*token = strtok(com, " ")
    // commands.push_back(com);
}

void Command::display() {
  for(int i = 0; i < commands.size(); ++i) {
      std::cout << commands.at(i) << std::endl;
  }
}
