#include "SEMICOLON.h"
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
SEMICOLON::SEMICOLON() {
    Connector();
    data = "";
}

// Constructor: Sets the left and right-hand sides of the AND connector.
SEMICOLON::SEMICOLON(Base* left, Base* right) {
    Connector(left, right);
    data = ";";
}

void SEMICOLON::setSEMIVector(std::string str1) {

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
      semis.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < semis.size(); ++i ) {
    if(semis.at(i) == ";") {
        tempSCV.push_back(semis.at(i));
    }
  }

  semiV.reserve(tempSCV.size());
  for(unsigned index = 0; index < tempSCV.size(); ++index) {
      semiV.push_back((char*)tempSCV[index].c_str());
  }
}

// Executes left and then executes right. Returns true if right executes.
bool SEMICOLON::execute(std::vector<char*> cmd) {
    lhs->execute(cmd);
    if(rhs->execute(cmd)) {
        return true;
    }
    return false;
}

void SEMICOLON::display() {
    for(unsigned i = 0; i < semiV.size(); ++i) {
        std::cout << semiV.at(i) << std::endl;
    }
}
