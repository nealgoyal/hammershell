#include "Test.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
//  protected:
//     vector<char*> commands;
//  public:

Test::Test() {
    flgPtr = NULL;
}

// Constructor: takes a vector of char* and loads the commands vector.
Test::Test(vector<char*> input) {
    if(input.size() != 0) {
        flgPtr = input.back();
        data = input.back();
    }
}

// Returns the data when pointed to in the main
string Test::getData() {
    return data;
}

// Takes in a char* and puts it into the vector of commands.
void Test::setTestVector(std::string str1) {

    typedef vector< string > split_vector_type;

    split_vector_type coms;
    split( coms, str1, is_any_of(" "), token_compress_on );
    for(unsigned i = 0; i < coms.size(); ++i) {
        trim(coms.at(i));
        flags.push_back(coms.at(i));
    }

    for(unsigned i = 0; i < flags.size(); ++i ) {
        if(flags.at(i) == "-e" || flags.at(i) == "-d" || flags.at(i) == "-f") {
            tmpFlags.push_back(flags.at(i));
        }
    }

    flgsVec.reserve(tmpFlags.size());
    flgs.reserve(tmpFlags.size());
    for(unsigned index = 0; index < tmpFlags.size(); ++index) {
        flgs.push_back((char*)tmpFlags[index].c_str());
        flgsVec.push_back((char*)tmpFlags[index].c_str());
    }
}

std::vector<char*> Test::getTestVectorReversed() {
    revFlg = flgsVec;
    std::reverse(revFlg.begin(), revFlg.end());
    return revFlg;
}

// Executes commands
// bool Command::execute() {
//     // cout << "EXEC" << endl;
//     pid_t pid = fork(); // Creates child process through fork
//     if(pid == 0) { // Child Process
//
//         // Convert the data to a char[]
//         char ex[420]; // Blaze it
//         int args = 1;
//         // Populates ex[] with contents of data; counts amount of arguments
//         for(unsigned i = 0; i < data.size(); i++) {
//             ex[i] = data[i];
//             if(data[i] == ' ') { // Tracks number of spaces
//                 ++args;
//             }
//         }
//         ex[data.size()] = '\0'; // Set last value in ex[] to null
//
//         // Need to create char** for execvp()
//         // Note: Justin hasn't studied the boost library :(
//         char* argument;
//         argument = strtok(ex, " ");
//         char** execArg = new char*[args + 1];
//         for(unsigned j = 0; argument != NULL; ++j) {
//             execArg[j] = new char[strlen(argument)];
//             strcpy(execArg[j], argument);
//             argument = strtok(NULL, " ");
//         }
//         execArg[args] = NULL; //Sets last value in execArg[] to null
//
//         // Call execvp
//         if(execvp(execArg[0], execArg) == -1) {
//             perror("Failed to Execute");
//             exit(0);
//             return false;
//         }
//         return true;
//     } else if(pid > 0) { // Parent Process
//         // cout << "ENTERED PID" << endl;
//         int status;
//         waitpid(pid, &status, 0);
//         if(WEXITSTATUS(status) == 1) {
//             // cout << "ENTERED STAT" << endl;
//             return false;
//         }
//     } else {
//         // cout << "ENTERED PERR" << endl;
//         perror("Fork Failed"); // Failed
//         exit(1);
//     }
//     // cout << "DONE" << endl;
//     return true;
// }

// Displays all of the contents of the vector of commands.
void Test::display() {
  for(unsigned i = 0; i < flgs.size(); ++i) {
      std::cout << flgs.at(i) << std::endl;
  }
}
