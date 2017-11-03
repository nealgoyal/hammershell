#ifndef AND_H
#define AND_H

#include "Connector.h"

class AND : public Connector {
 public:
    AND() {}
    void setConVector();
    bool execute();
};

#endif;
