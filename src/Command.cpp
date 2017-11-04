#include "Command.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

//  protected:
//     vector<char*> commands;
//  public:

// Constructor: takes a vector of char* and loads the commands vector.
Command::Command(std::vector<char*> input) {
    commands = input;
}

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(char* input) {
    char delim[] = "|&;";
    //cout << "The tokens are:" << endl;
    char *token = strtok(input,delim);
    commands.push_back(token);
}

bool Command::execute(char* left, char* right) {
    /*
    pid_t pid = fork(); // Creates child process through fork
    if(pid == 0) {
        if(execvp(left, right) == -1) {
            perror("exec");
            return false;
        }
    } else if(pid > 0) {
        if(wait(0) == -1) {
            perror("wait");
        }
    } else {
        perror("fork");
    }
    */
    return false;
}

// Displays all of the contents of the vector of commands.
void Command::display() {
    for(int i = 0; i < commands.size(); ++i) {
        std::cout << commands.at(i) << std::endl;
    }
}
