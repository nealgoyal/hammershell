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
    // commands = input;
}

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(char* input) {
    char delim[] = "|&;";
    //cout << "The tokens are:" << endl;
    char *token = strtok(input,delim);
    commands.push_back(token);
}

bool Command::execute(std::vector<char*> cmd) {
    pid_t pid = fork(); // Creates child process through fork
    if(pid == 0) { // Child Process
        if(execvp(cmd[0], cmd.data()) == -1) {
            perror("Failed to Execute");
            exit(1);
        }
    } else if(pid > 0) { // Parent Process
        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) == 1) {
            return false;
        }
    } else {
        perror("Fork Failed"); // Failed
        exit(1);
    }
    return true;
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
