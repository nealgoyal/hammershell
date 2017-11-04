#include "Exit.h"
#include <iostream>
#include <cstdlib>

// Checks if there are any commands in the vector. If not, exit and return true.
bool Exit::execute(std::vector<char*>) {
    // if(commands.empty()) {
    //     exit(0);
    //     return true;
    // }
    // return false;
    exit(0);
}
