#include "DoubleOutputRedirect.h"
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
DoubleOutputRedirect::DoubleOutputRedirect() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the AND connector.
DoubleOutputRedirect::DoubleOutputRedirect(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = ">>";
}

void DoubleOutputRedirect::setdoutVector(std::string str1) {

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
      douts.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < douts.size(); ++i ) {
    if(douts.at(i) == ">>") {
        tempDOR.push_back(douts.at(i));
    }
  }

  doutV.reserve(tempDOR.size());
  for(unsigned index = 0; index < tempDOR.size(); ++index) {
      doutV.push_back((char*)tempDOR[index].c_str());
  }
}

// Executes right side if left side DOES execute.
// Returns true if right side executes.
bool DoubleOutputRedirect::execute() {
    if(lhs->execute()) {
        if(rhs->execute()) {
            return true;
        }
        return false;
    }
    return false;
}

void DoubleOutputRedirect::display() {
    for(unsigned i = 0; i < doutV.size(); ++i) {
        std::cout << doutV.at(i) << std::endl;
    }
}
