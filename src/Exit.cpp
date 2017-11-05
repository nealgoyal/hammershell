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
    for(int i = 0; i < commands.size(); ++i) {
      if(commands.at(i) == "exit" || commands.at(i) == "Exit") {
          exit(0);
          return true;
      }
    }
    return false;
}
