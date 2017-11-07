#include "Exit.h"
#include <iostream>
#include <cstdlib>

// Simply exits the program.
bool Exit::execute(std::vector<char*> cmd) {
    exit(0);
    return true;
    /*
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
    */
}
