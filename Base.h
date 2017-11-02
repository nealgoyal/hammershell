#ifndef BASE_H
#define BASE_H

class Base {
 private:
    Base* child;
 public:
    Base() {}
    virtual bool execute() = 0;
};

#endif
