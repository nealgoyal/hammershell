#ifndef COMMAND_H
#define COMMAND_H

#include "Base.h"
#include "string.h"
#include <vector>

class Command : public Base {
 protected:
    std::vector<char*> commands;
 public:
    Command() {}
    Command(std::vector<char*>);
    void setComVector(char*);
    virtual bool execute(char*, char*);
    void display();
};

#endif
