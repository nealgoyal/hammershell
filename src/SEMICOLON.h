#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"

class SEMICOLON : public Connector {
 public:
    SEMICOLON() {}
    void setConVector(char*);
    bool execute();
};

#endif