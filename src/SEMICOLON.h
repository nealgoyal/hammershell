#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"

class SEMICOLON : public Connector {
private:
  std::vector<std::string> semis;
  std::vector<std::string> tempSCV;
  std::string input;
  std::vector<char*> semiV;
 public:
    SEMICOLON() {}
    SEMICOLON(std::string);
    void setSEMIVector(std::string);
    bool execute(std::vector<char*> cmd);
    void display();
};

#endif
