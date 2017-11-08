#include "Exit.h"
#include <iostream>
#include <cstdlib>

// Simply exits the program.
bool Exit::execute() {
    exit(0);
    return true;
}