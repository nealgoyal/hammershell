#ifndef INPUTREDIRECT_H
#define INPUTREDIRECT_H

#include "Connector.h"

class InputRedirect : public Connector {
 private:
    std::vector<std::string> inps;
    std::vector<std::string> tempIR;
    std::vector<char*> inpV;
 public:
    InputRedirect();
    InputRedirect(Base*, Base*);
    void setinpVector(std::string);
    bool execute();
    void display();
};

#endif
