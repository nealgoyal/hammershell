#include "Command.h"

//  private:
//     vector<string> commands;
//  public:

Command::Command() {

}

//Constructor. Passes in a vector of strings and loads the commands vector.
Command::Command(std::vector<std::string> input) {
    for(int i = 0; i < input.size(); ++i) {
        commands.at(i) = input.at(i);
    }
}

void Command::setComVector(std::string com) {
    commands.push_back(com);
}



