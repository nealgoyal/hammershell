#include "Parser.h"
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

Parser::Parser() {}
Parser::Parser(vector <string> input) {
    inp = input;
}

bool Parser::execute(char * cmd) {
  pid_t pid = fork(); // Creates child process through fork
  if(pid == 0) { // Child Process
      if(execvp(cmd[0], cmd) == -1) {
          perror("Failed to Execute");
          return false;
      }
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
  // cout << "DONE" << endl;
  return true;
}
