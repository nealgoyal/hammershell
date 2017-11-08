#include "Command.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
//  protected:
//     vector<char*> commands;
//  public:

Command::Command() {
    cmdPtr = NULL;
}

// Constructor: takes a vector of char* and loads the commands vector.
Command::Command(vector<char*> input) {
    if(input.size() != 0) {
        cmdPtr = input.back();
        data = input.back();
    }
}

// Returns the data when pointed to in the main
string Command::getData() {
    return data;
}

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(std::string str1) {

    replace(str1.begin(), str1.end(), '&', '!');
    replace(str1.begin(), str1.end(), '|', '!');
    replace(str1.begin(), str1.end(), ';', '!');

    // cout << str1 << endl;

    typedef vector< string > split_vector_type;

    split_vector_type coms;
    split( coms, str1, is_any_of("!"), token_compress_on );
    // commands.size() = coms.size();
    for(unsigned i = 0; i < coms.size(); ++i) {
        trim(coms.at(i));
        commands.push_back(coms.at(i));
        // strcpy(commands.at(i), coms.at(i).c_str());
    }

    cmdVec.reserve(commands.size());
    cmds.reserve(commands.size());
    for(unsigned index = 0; index < commands.size(); ++index) {
        cmds.push_back((char*)commands[index].c_str());
        cmdVec.push_back((char*)commands[index].c_str());
        // cmds[index] = (char*)commands[index].c_str();
        // cout << cmds[index] << endl;
    }
}

std::vector<char*> Command::getComVectorReversed() {
    revCmd = cmdVec;
    std::reverse(revCmd.begin(), revCmd.end());
    return revCmd;
}

bool Command::execute() {
    pid_t pid = fork(); // Creates child process through fork
    if(pid == 0) { // Child Process
        // char* ex[100];
        // for(unsigned i = 0; cmdPtr[i] != ' '; ++i) {
        //     ex[i] = cmdPtr[i];
        // }
        // std::cout << "Executable: " << ex << ", arguments: " << cmdPtr << std::endl;
        
        // if(execvp(ex[0], ex) == -1) {
        //     perror("Failed to Execute");
        //     return false;
        // }
    } else if(pid > 0) { // Parent Process
        // cout << "ENTERED PID" << endl;
        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) == 1) {
            // cout << "ENTERED STAT" << endl;
            return false;
        }
    } else {
        // cout << "ENTERED PERR" << endl;
        perror("Fork Failed"); // Failed
        exit(1);
    }
    // cout << "DONE" << endl;
    return true;
}

// Displays all of the contents of the vector of commands.
void Command::display() {
  for(unsigned i = 0; i < cmds.size(); ++i) {
      std::cout << cmds.at(i) << std::endl;
  }
}
