#include "Command.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

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

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(std::string str1) {
   
    replace(str1.begin(), str1.end(), '&', '!');
    replace(str1.begin(), str1.end(), '|', '!');
    replace(str1.begin(), str1.end(), ';', '!');
    replace(str1.begin(), str1.end(), '<', '!');
    replace(str1.begin(), str1.end(), '>', '!');

    typedef vector< string > split_vector_type;

    split_vector_type coms;
    split( coms, str1, is_any_of("!"), token_compress_on );
    for(unsigned i = 0; i < coms.size(); ++i) {
        trim(coms.at(i));
        commands.push_back(coms.at(i));
    }

    cmdVec.reserve(commands.size());
    cmds.reserve(commands.size());
    for(unsigned index = 0; index < commands.size(); ++index) {
        cmds.push_back((char*)commands[index].c_str());
        cmdVec.push_back((char*)commands[index].c_str());
    }
}

std::vector<char*> Command::getComVectorReversed() {
    revCmd = cmdVec;
    std::reverse(revCmd.begin(), revCmd.end());
    return revCmd;
}

// Executes the test command
bool Command::testCommand() {
    struct stat sendHelp;
    if((getData().substr(5,2) != "-e") && (getData().substr(5,2) != "-d")
         && (getData().substr(5,2) != "-f")) {
        if(getData().substr(5,1) != "-") {
            std::string str = "-e ";
            data.insert(5, str);
            // cout << "Data after insert: " << getData() << endl;
            // cout << "Flag: " << getData().substr(5,2) << endl;
            // cout << "Argument after flag: " << getData().substr(8) << endl;
        } else {
            perror("Invalid flag");
            return false;
        }
    }
    // Inputs everything after flag
    if(stat((getData().substr(8)).c_str(), &sendHelp) == -1) {
        cout << "(False)" << endl;
        return false;
    }
    // Executes test command based on flag
    if((getData().substr(5,2) == "-e" && sendHelp.st_mode) ||
      (getData().substr(5,2) == "-d" && S_ISDIR(sendHelp.st_mode)) ||
      (getData().substr(5,2) == "-f" && S_ISREG(sendHelp.st_mode))) {
        cout << "(True)" << endl;
        return true;
    }
    cout << "(False)" << endl;
    return false;
}

// Executes commands
bool Command::execute() {
    if(getData().substr(0,4) == "test") {
        // cout << "Data: " << getData() << endl;
        // cout << "Flag: " << getData().substr(5,2) << endl;
        // cout << "Argument after flag: " << getData().substr(8) << endl;
        testCommand();
    } else {
        // cout << "EXEC" << endl;
        pid_t pid = fork(); // Creates child process through fork
        if(pid == 0) { // Child Process

            // Convert the data to a char[]
            char ex[420]; // Blaze it
            int args = 1;
            // Populates ex[] with contents of data; counts amount of arguments
            for(unsigned i = 0; i < data.size(); i++) {
                ex[i] = data[i];
                if(data[i] == ' ') { // Tracks number of spaces
                    ++args;
                }
            }
            ex[data.size()] = '\0'; // Set last value in ex[] to null

            // Need to create char** for execvp()
            // Note: Justin hasn't studied the boost library :(
            char* argument;
            argument = strtok(ex, " ");
            char** execArg = new char*[args + 1];
            for(unsigned j = 0; argument != NULL; ++j) {
                execArg[j] = new char[strlen(argument)];
                strcpy(execArg[j], argument);
                argument = strtok(NULL, " ");
            }
            execArg[args] = NULL; //Sets last value in execArg[] to null

            // Call execvp
            if(execvp(execArg[0], execArg) == -1) {
                perror("Command not found");
                return false;
            }
            return true;
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
    return true;
}

// Returns the data when pointed to in the main
std::string Command::getData() {
    return data;
}

// Displays all of the contents of the vector of commands.
void Command::display() {
  for(unsigned i = 0; i < cmds.size(); ++i) {
      std::cout << cmds.at(i) << std::endl;
  }
}
