#include "InputRedirect.h"
#include <vector>
#include <string>
#include <cstring>

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

// class InputRedirect : public Connector {
//  public:

// Default Constructor
InputRedirect::InputRedirect() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the < connector.
InputRedirect::InputRedirect(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = "<";
}

void InputRedirect::setinpVector(std::string str1) {

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
        inps.push_back(cnts.at(i));
    }

    for(unsigned i = 0; i < inps.size(); ++i ) {
        if(inps.at(i) == "<") {
            tempIR.push_back(inps.at(i));
        }
    }

    inpV.reserve(tempIR.size());
    for(unsigned index = 0; index < tempIR.size(); ++index) {
        inpV.push_back((char*)tempIR[index].c_str());
    }
    }

// Passes in rhs as input and standard output(1)
// Calls execute on lhs to execute the actual command.
bool InputRedirect::execute() {
    // Sets input to the rhs
    int in = open((rhs->getData()).c_str(), O_RDONLY);
    // Makes a copy of the file descriptor of user input
    int userInput = dup(0);
    if(dup2(in, 0) == -1) {
        close(in);
        dup2(userInput, 0);
        close(userInput);
        return false;
    }
    if(lhs->execute() == false) {
        close(in);
        dup2(userInput, 0);
        close(userInput);
        return false;
    }
    close(in);
    dup2(userInput, 0);
    close(userInput);
    return true;
}

void InputRedirect::display() {
    for(unsigned i = 0; i < inpV.size(); ++i) {
        std::cout << inpV.at(i) << std::endl;
    }
}
