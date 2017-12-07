#include "Pipe.h"
#include <vector>
#include <string>
#include <cstring>

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

// class Pipe : public Connector {
//  public:

// Default Constructor
Pipe::Pipe() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the Pipe connector.
Pipe::Pipe(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = "|";
}

void Pipe::setpipeVector(std::string str1) {
    std::string str2 = " ";
    for(unsigned i = 0; i < str1.length(); ++i) {
        if(str1.at(i) == ';') {
            str1.insert(i, str2);
            i++;
        }
    }

    typedef vector< string > split_vector_type;

    split_vector_type cnts;
    split( cnts, str1, is_any_of(" "), token_compress_on );
    for(unsigned i = 0; i < cnts.size(); ++i) {
        pipes.push_back(cnts.at(i));
    }

    for(unsigned i = 0; i < pipes.size(); ++i ) {
        if(pipes.at(i) == "|") {
            tempP.push_back(pipes.at(i));
        }
    }

    pipeV.reserve(tempP.size());
    for(unsigned index = 0; index < tempP.size(); ++index) {
        pipeV.push_back((char*)tempP[index].c_str());
    }
}

// Executes right side if left side DOES execute.
// Returns true if right side executes.
bool Pipe::execute() {
    int fds[2];

    if(pipe(fds) == -1) {
        return false;
    }
    cout << "Made pipe" << endl;
    pid_t pid = fork();
    if(pid == 0) {
        cout << "Entered child process" << endl;
        close(fds[0]);
        cout << "Closed unused half of lhs" << endl;
        // Outputs lhs to fds[1] instead of stdout;
        if(dup2(fds[1], 1) == -1) {
            cout << "Dup2 failed" << endl;
            close(fds[1]);
            exit(1);
        }
        if(lhs->execute() == false) {
            close(fds[1]);
            exit(1);
        }
        cout << "Duplicated new input" << endl;
        close(fds[1]);
        cout << "Closed fds[1]" << endl;
        exit(0);
    } else if(pid > 0) { // Parent Process
        cout << "Entered parent process" << endl;
        close(fds[1]);
        cout << "Closed unused half of rhs" << endl;
        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) == 1) {
            return false;
        }
        cout << "Child terminated" << endl;
        // Sends output through as new input and outputs to stdout
        int userInput = dup(0);
        cout << "Stores stdin" << endl;
        if(dup2(fds[0], 0) == -1) {
            close(fds[0]);
            dup2(userInput, 0);
            close(userInput);
            return false;
        }
        cout << "Duplicates input" << endl;
        if(rhs->execute() == false) {
            cout << "Couldn't execute rhs" << endl;
            close(fds[0]);
            dup2(userInput, 0);
            close(userInput);
            return false;
        }
        cout << "Executed rhs" << endl;
        close(fds[0]);
        dup2(userInput, 0);
        close(userInput);
        return true;
    } else {
        perror("Fork Failed"); // Failed
        exit(1);
    }

    return true;
}

void Pipe::display() {
    for(unsigned i = 0; i < pipeV.size(); ++i) {
        std::cout << pipeV.at(i) << std::endl;
    }
}
