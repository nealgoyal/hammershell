#ifndef BASE_H
#define BASE_H

#include <iostream>

class Base {
 public:
    Base() {}
    virtual bool execute() = 0;
};

#endif
