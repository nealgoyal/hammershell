#include "Test.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

Test::Test() {
    flgPtr = NULL;
}

// Constructor: takes a vector of char* and loads the tests vector.
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

// Takes in a char* and puts it into the vector of tests.
void Test::setTestVector(std::string str1) {

    typedef vector< string > split_vector_type;

    split_vector_type coms;
    split( coms, str1, is_any_of(" "), token_compress_on );
    for(unsigned i = 0; i < coms.size(); ++i) {
        trim(coms.at(i));
        flags.push_back(coms.at(i));
    }

    for(unsigned i = 0; i < flags.size(); ++i ) {
        if(flags.at(i) == "-e") {
            tmpFlags.push_back("e");
        }
        if(flags.at(i) == "-d") {
            tmpFlags.push_back("d");
        }
        if(flags.at(i) == "-f") {
            tmpFlags.push_back("f");
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

// Executes Test
bool Test::execute() {
    struct stat sendHelp;
    if(tmpFlags.front() != "-e" && tmpFlags.front() != "-d" && tmpFlags.front() != "-f") {
        perror("Invalid flag");
        return false;
    }
    //flgsVec.front() ?
    if(stat(const_cast<char*>(flgsVec.front()), &sendHelp) == -1) {
        cout << "(False)" << endl;
        return false;
    }
    // if((tmpFlags.front() == "-e" && sendHelp.st_mode) ||
    //    (tmpFlags.front() == "-d" && S_ISDIR(sendHelp.st_mode)) ||
    //    (tmpFlags.front() == "-f" && S_ISREG(sendHelp.st_mode))) {
    if(sendHelp.st_mode) {
        cout << "(True)" << endl;
        return true;
    }
    cout << "(False)" << endl;
    return false;
}

// Displays all of the contents of the vector of commands.
void Test::display() {
  for(unsigned i = 0; i < flgs.size(); ++i) {
      std::cout << flgs.at(i) << std::endl;
  }
}
