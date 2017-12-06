#include "InputRedirect.h"
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
InputRedirect::InputRedirect() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the AND connector.
InputRedirect::InputRedirect(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = "<";
}

void InputRedirect::setinpVector(std::string str1) {

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
      inps.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < inps.size(); ++i ) {
    if(inps.at(i) == "<") {
        tempIR.push_back(inps.at(i));
    }
  }

  inpV.reserve(tempIR.size());
  for(unsigned index = 0; index < tempIR.size(); ++index) {
      inpV.push_back((char*)tempIR[index].c_str());
  }
}

// Executes right side if left side DOES execute.
// Returns true if right side executes.
bool InputRedirect::execute() {
    if(lhs->execute()) {
        if(rhs->execute()) {
            return true;
        }
        return false;
    }
    return false;
}

void InputRedirect::display() {
    for(unsigned i = 0; i < inpV.size(); ++i) {
        std::cout << inpV.at(i) << std::endl;
    }
}
