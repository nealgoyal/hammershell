#ifndef PIPE_H
#define PIPE_H

#include "Connector.h"

class Pipe : public Connector {
 private:
    std::vector<std::string> pipes;
    std::vector<std::string> tempP;
    std::vector<char*> pipeV;
 public:
    Pipe();
    Pipe(Base*, Base*);
    void setpipeVector(std::string);
    bool execute();
    void display();
};

#endif
