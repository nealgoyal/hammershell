#ifndef EXIT_H
#define EXIT_H

#include "Command.h"

class Exit : public Command {
 public:
    Exit() {}
    bool execute(std::vector<char*>);
};

#endif
