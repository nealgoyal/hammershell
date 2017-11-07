#ifndef AND_H
#define AND_H

#include "Connector.h"

class AND : public Connector {
private:
  std::vector<std::string> tempV;
 public:
    AND() {}
    void setANDVector(char*);
    bool execute(std::vector<char*> cmd);
};

#endif
