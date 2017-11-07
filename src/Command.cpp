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
        cmdPtr = input.at(0);
        data = input.at(0);
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
    //
    // if(!execute(cmds)) {
    //   cout << "NO";
    // }
    // else {
    //   cout << "YES";
    // }

    // Populates vector of char* for execute
    // for(int i = 0; i < commands.size(); ++i) {
    //     exCmd[i] = &commands[i][0];
    // }
    // execute(exCmd); -> Seg fault
}

std::vector<char*> Command::getComVector() {
    return cmdVec;
}

bool Command::execute(std::vector<char*> exCmd) {
    pid_t pid = fork(); // Creates child process through fork
    if(pid == 0) { // Child Process
        if(execvp(exCmd[0], exCmd.data()) == -1) {
            perror("Failed to Execute");
            return false;
        }
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
    //std::cout << commands.at(0) << std::endl;
    //std::cout << commands.at(1) << std::endl;
    //std::cout << commands.at(2) << std::endl;
}
