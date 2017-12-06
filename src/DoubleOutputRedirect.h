#ifndef DOUBLEOUTPUTREDIRECT_H
#define DOUBLEOUTPUTREDIRECT_H

#include "Connector.h"

class DoubleOutputRedirect : public Connector {
 private:
    std::vector<std::string> douts;
    std::vector<std::string> tempDOR;
    std::vector<char*> doutV;
 public:
    DoubleOutputRedirect();
    DoubleOutputRedirect(Base*, Base*);
    void setdoutVector(std::string);
    bool execute();
    void display();
};

#endif
