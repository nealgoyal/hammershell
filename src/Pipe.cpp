#include "Pipe.h"
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
Pipe::Pipe() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the AND connector.
Pipe::Pipe(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = "|";
}

void Pipe::setpipeVector(std::string str1) {

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
      pipes.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < pipes.size(); ++i ) {
    if(pipes.at(i) == "|") {
        tempP.push_back(pipes.at(i));
    }
  }

  pipeV.reserve(tempP.size());
  for(unsigned index = 0; index < tempP.size(); ++index) {
      pipeV.push_back((char*)tempP[index].c_str());
  }
}

// Executes right side if left side DOES execute.
// Returns true if right side executes.
bool Pipe::execute() {
    if(lhs->execute()) {
        if(rhs->execute()) {
            return true;
        }
        return false;
    }
    return false;
}

void Pipe::display() {
    for(unsigned i = 0; i < pipeV.size(); ++i) {
        std::cout << pipeV.at(i) << std::endl;
    }
}
