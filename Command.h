#ifndef COMMAND_H
#define COMMAND_H

#include "Base.h"
#include <vector>
#include <cstring>
#include <stdio.h>

class Command : public Base {
 protected:
    std::vector<char*> commands;
 public:
    Command();
    Command(std::vector<std::string>);
    void setComVector(std::string);
    virtual bool execute();
};

#endif
