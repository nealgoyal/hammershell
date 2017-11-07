#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"
#include <vector>
#include <string>

class Connector : public Base {
public:
    Base* lhs;
    Base* rhs;
    std::vector<std::string> connectors;
    std::vector<std::string> tempContainer;
    std::vector<char*> cntr;
 public:
    Connector();
    Connector(Base*, Base*);
    void setConVector(std::string);
    std::vector<char*> getConVector();
    virtual bool execute(std::vector<char*>);
    void display();
};

#endif
