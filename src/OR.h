#ifndef OR_H
#define OR_H

#include "Connector.h"

class OR : public Connector {
private:
  std::vector<std::string> ors;
  std::vector<std::string> tempOV;
  std::string input;
  std::vector<char*> orV;
 public:
    OR() {}
    OR(std::string);
    void setORVector(std::string);
    bool execute(std::vector<char*> cmd);
    void display();
};

#endif
