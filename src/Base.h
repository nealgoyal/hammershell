#ifndef BASE_H
#define BASE_H

class Base {
 public:
    Base() {}
    virtual bool execute(char*, char*) = 0;
};

#endif
