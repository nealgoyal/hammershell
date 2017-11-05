#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"
#include <vector>
#include <string>

class Connector : public Base {
 protected:
    std::vector<std::string> connectors;
    std::string input;
    std::vector<const char*> cntr;
 public:
    Connector() {}
    Connector(std::string);
    void setConVector(std::string);
    virtual bool execute(std::vector<char*>);
    void display();
};

#endif
