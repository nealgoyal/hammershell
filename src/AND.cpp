#include "AND.h"
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
AND::AND() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the AND connector.
AND::AND(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = "&&";
}

void AND::setANDVector(std::string str1) {

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
      ands.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < ands.size(); ++i ) {
    if(ands.at(i) == "&&") {
        tempAV.push_back(ands.at(i));
    }
  }

  andV.reserve(tempAV.size());
  for(unsigned index = 0; index < tempAV.size(); ++index) {
      andV.push_back((char*)tempAV[index].c_str());
  }
}

// Executes right side if left side DOES execute.
// Returns true if right side executes.
bool AND::execute() {
    if(lhs->execute()) {
        if(rhs->execute()) {
            return true;
        }
        return false;
    }
    return false;
}

void AND::display() {
    for(unsigned i = 0; i < andV.size(); ++i) {
        std::cout << andV.at(i) << std::endl;
    }
}
