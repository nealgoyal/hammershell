#ifndef AND_H
#define AND_H

#include "Connector.h"

class AND : public Connector {
 public:
    AND() {}
    void setConVector(char*);
    bool execute();
};

#endif