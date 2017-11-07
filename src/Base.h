#ifndef BASE_H
#define BASE_H
#include <vector>

class Base {
 public:
    Base() {}
    virtual bool execute(std::vector<char*>) = 0;
};
#endif
