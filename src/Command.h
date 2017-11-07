#ifndef COMMAND_H
#define COMMAND_H

#include "Base.h"
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Command : public Base {
 protected:
    char* cmdPtr;
    string data;
    std::vector<std::string> commands;
    std::vector<const char*> cmds;
    std::vector<char*> cmdVec;
    std::vector<char*> exCmd;
    std::string input;
 public:
    Command();
    Command(vector<char*>);
    string getData();    
    void setComVector(std::string);
    std::vector<char*> getComVector();
    virtual bool execute(std::vector<char*>);
    void display();
};

#endif
