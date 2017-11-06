#include "Connector.h"
#include "string.h"
#include <vector>
#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#include <boost/algorithm/string.hpp>
using namespace boost;
using namespace std;

// std::vector<char*> connectors

// Constructor: takes a vector of char* and loads the connectors vector.
Connector::Connector(std::string input) {
    this->input = input;
}

// Takes in a char* and puts it into the vector of connectors.
void Connector::setConVector(std::string str1) {

  std::string str2 = " ";
  for(int i = 0; i < str1.length(); ++i) {
      if(str1.at(i) == ';') {
        // str1.insert(i, str2);
        str1.replace(i,str1.length(),str2);
      }
  }

  cout << str1 << endl;

  typedef vector< string > split_vector_type;

  split_vector_type cnts;
  split( cnts, str1, is_any_of(" "), token_compress_on );
  for(int i = 0; i < cnts.size(); ++i) {
      connectors.push_back(cnts.at(i));
  }

  for( int i = 0; i < connectors.size(); ++i ) {
    if(connectors.at(i) == ";" || connectors.at(i) == "&&" || connectors.at(i) == "||") {
        tempContainer.push_back(connectors.at(i));
    }
  }

  cntr.reserve(tempContainer.size());
  for(int index = 0; index < tempContainer.size(); ++index) {
      cntr.push_back(tempContainer[index].c_str());
  }

}

bool Connector::execute(std::vector<char*> cnt) {
    pid_t pid = fork(); // Creates child process through fork
    if(pid == 0) { // Child Process
        if(execvp(cnt[0], cnt.data()) == -1) {
            perror("Failed to Execute");
            exit(1);
        }
    } else if(pid > 0) { // Parent Process
        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) == 1) {
            return false;
        }
    } else {
        perror("Fork Failed"); // Failed
        exit(1);
    }
    return true;
}

// Displays all of the contents of the vector of connectors."
void Connector::display() {
    for(unsigned i = 0; i < cntr.size(); ++i) {
        std::cout << cntr.at(i) << std::endl;
    }
}
