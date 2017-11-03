#ifndef OR_H
#define OR_H

#include "Connector.h"

class OR : public Connector {
 public:
    OR() {}
    void setConVector(char*);
    bool execute();
};

#endif