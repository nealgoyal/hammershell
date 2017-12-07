#ifndef BASE_H
#define BASE_H
#include <vector>
#include <string>

class Base {
 public:
    Base() {}
    virtual bool execute() = 0;
    virtual std::string getData() = 0;
};
#endif
