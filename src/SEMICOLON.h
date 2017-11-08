#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"

class SEMICOLON : public Connector {
private:
  std::vector<std::string> semis;
  std::vector<std::string> tempSCV;
  std::vector<char*> semiV;
 public:
    SEMICOLON();
    SEMICOLON(Base*, Base*);
    void setSEMIVector(std::string);
    bool execute();
    void display();
};

#endif
