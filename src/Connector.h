#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"
#include <vector>

class Connector : public Base {
 protected:
    std::vector<char*> connectors;
 public:
    Connector() {}
    Connector(std::vector<char*>);
    virtual void setConVector(char*);
    virtual bool execute();
};

#endif