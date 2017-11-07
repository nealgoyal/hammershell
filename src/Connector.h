#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"
#include <vector>
#include <string>

class Connector : public Base {
 protected:
    std::vector<std::string> connectors;
    std::vector<std::string> tempContainer;
    std::string input;
    std::vector<char*> cntr;
 public:
    Connector() {}
    Connector(std::string);
    void setConVector(std::string);
    virtual bool execute(std::vector<char*>);
    void display();
};

#endif
