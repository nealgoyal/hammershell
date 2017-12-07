#include "OutputRedirect.h"
#include <vector>
#include <string>
#include <cstring>

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

// class OutputRedirect : public Connector {
//  public:

// Default Constructor
OutputRedirect::OutputRedirect() : Connector() {
    data = "";
}

// Constructor: Sets the left and right-hand sides of the > connector.
OutputRedirect::OutputRedirect(Base* left, Base* right) {
    lhs = left;
    rhs = right;
    data = ">";
}

void OutputRedirect::setoutVector(std::string str1) {

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
      outs.push_back(cnts.at(i));
  }

  for(unsigned i = 0; i < outs.size(); ++i ) {
    if(outs.at(i) == ">") {
        tempOR.push_back(outs.at(i));
    }
  }

  outV.reserve(tempOR.size());
  for(unsigned index = 0; index < tempOR.size(); ++index) {
      outV.push_back((char*)tempOR[index].c_str());
  }
}

// Passes in rhs as input and standard output(1)
// Calls execute on lhs to execute the actual command.
bool OutputRedirect::execute() {
    // Sets input to the rhs
    int out = open((rhs->getData()).c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    
    pid_t pid = fork();
    if(pid == 0) {
        if(dup2(out, 1) == -1) {
            close(out);
            exit(1);
        }
        if(lhs->execute() == false) {
            close(out);
            exit(1);
        }
        exit(0);
    } else if(pid > 0) { // Parent Process
        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) == 1) {
            return false;
        }
    } else {
        // cout << "ENTERED PERR" << endl;
        perror("Fork Failed"); // Failed
        exit(1);
    }

    close(out);

    return true;
}

void OutputRedirect::display() {
    for(unsigned i = 0; i < outV.size(); ++i) {
        std::cout << outV.at(i) << std::endl;
    }
}
