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
    std::vector<char*> revCmd;
    std::string input;
 public:
    Command();
    Command(vector<char*>);
    string getData();    
    void setComVector(std::string);
    std::vector<char*> getComVectorReversed();
    virtual bool execute();
    void display();
};

#endif