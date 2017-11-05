#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"
#include <vector>

class Connector : public Base {
 protected:
    std::vector<char*> connectors;
    std::string input;
 public:
    Connector() {}
    Connector(std::string);
    void setConVector(std::string);
    // virtual bool execute(char*, char*);
    void display();
};

#endif
