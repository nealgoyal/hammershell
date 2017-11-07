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

// Pushes back an "&" character into the connector vector.
AND::AND(std::string input) {
    this->input = input;
}

void AND::setANDVector(std::string str1) {

  std::string str2 = " ";
  for(int i = 0; i < str1.length(); ++i) {
      if(str1.at(i) == ';') {
        str1.insert(i, str2);
        i++;
      }
  }

  typedef vector< string > split_vector_type;

  split_vector_type cnts;
  split( cnts, str1, is_any_of(" "), token_compress_on );
  for(int i = 0; i < cnts.size(); ++i) {
      ands.push_back(cnts.at(i));
  }

  for( int i = 0; i < ands.size(); ++i ) {
    if(ands.at(i) == "&&") {
        tempAV.push_back(ands.at(i));
    }
  }

  andV.reserve(tempAV.size());
  for(int index = 0; index < tempAV.size(); ++index) {
      andV.push_back((char*)tempAV[index].c_str());
  }
}

// Verifies that the && has been executed.
bool AND::execute(std::vector<char*> cmd) {
  // pid_t pid = fork(); // Creates child process through fork
  // if(pid == 0) { // Child Process
  //     if(execvp(cmd[0], cmd.data()) == -1) {
  //         perror("Failed to Execute");
  //         exit(1);
  //     }
  // } else if(pid > 0) { // Parent Process
  //     int status;
  //     waitpid(pid, &status, 0);
  //     if(WEXITSTATUS(status) == 1) {
  //         return false;
  //     }
  // } else {
  //     perror("Fork Failed"); // Failed
  //     exit(1);
  // }
  return true;
}

void AND::display() {
    for(unsigned i = 0; i < andV.size(); ++i) {
        std::cout << andV.at(i) << std::endl;
    }
}
