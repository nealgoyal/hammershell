#ifndef OUTPUTREDIRECT_H
#define OUTPUTREDIRECT_H

#include "Connector.h"

class OutputRedirect : public Connector {
 private:
    std::vector<std::string> outs;
    std::vector<std::string> tempOR;
    std::vector<char*> outV;
 public:
    OutputRedirect();
    OutputRedirect(Base*, Base*);
    void setoutVector(std::string);
    bool execute();
    void display();
};

#endif
