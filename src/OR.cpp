#include "OR.h"
#include <vector>
#include <string>
#include <cstring>

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

// class AND : public Connector {
//  public:

// Default Constructor
OR::OR() {
    Connector();
    data = "";
}

// Constructor: Sets the left and right-hand sides of the AND connector.
OR::OR(Base* left, Base* right) {
    Connector(left, right);
    data = "||";
}

void OR::setORVector(std::string str1) {

  std::string str2 = " ";
  for(unsigned i = 0; i < str1.length(); ++i) {
      if(str1.at(i) == ';') {
        str1.insert(i, str2);
        i++;
      }
  }

  typedef vector< string > split_vector_type;

  split_vector_type cnts;
  split( cnts, str1, is_any_of(" "), token_compress_on );
  for(unsigned i = 0; i < cnts.size(); ++i) {
      ors.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < ors.size(); ++i ) {
    if(ors.at(i) == "||") {
        tempOV.push_back(ors.at(i));
    }
  }

  orV.reserve(tempOV.size());
  for(unsigned index = 0; index < tempOV.size(); ++index) {
      orV.push_back((char*)tempOV[index].c_str());
  }
}

// Executes right side if left side does not execute.
// Returns true if right side executes.
bool OR::execute(std::vector<char*> cmd) {
    if(!lhs->execute(cmd)) {
        if(rhs->execute(cmd)) {
            return true;
        }
        return false;
    }
    return true;
}

void OR::display() {
    for(unsigned i = 0; i < orV.size(); ++i) {
        std::cout << orV.at(i) << std::endl;
    }
}
