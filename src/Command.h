#ifndef COMMAND_H
#define COMMAND_H

#include "Base.h"
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Command : public Base {
 protected:
    std::vector<std::string> commands;
<<<<<<< HEAD
    std::vector<char*> cmds;
=======
    std::vector<const char*> cmds;
    std::vector<char*> exCmd;    
>>>>>>> d017cb89c538326fd2381bac0f279ced38e5fb68
    std::string input;
 public:
    Command() {}
    Command(std::string);
    void setComVector(std::string);
    virtual bool execute(std::vector<char*>);
    void display();
};

#endif
