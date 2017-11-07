#ifndef AND_H
#define AND_H

#include "Connector.h"

class AND : public Connector {
private:
  std::vector<std::string> ands;
  std::vector<std::string> tempAV;
  std::string input;
  std::vector<char*> andV;
 public:
    AND() {}
    AND(std::string);
    void setANDVector(std::string);
    bool execute(std::vector<char*> cmd);
    void display();
};

#endif
