#ifndef COMMAND_H
#define COMMAND_H

#include "Base.h"
#include <vector>
#include <string>

class Command : public Base {
 private:
    std::vector<std::string> commands;
 public:
    Command();
    Command(std::vector<std::string>);
    void setComVector(std::string);
    virtual bool execute();
};

#endif
