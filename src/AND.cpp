#include "AND.h"
#include <iostream>

// class AND : public Connector {
//  public:

// Pushes back an "&" character into the connector vector.
void AND::setANDVector(char* And) {
  std::string str2 = " ";
  andV.reserve(cntr.size());
  for(int i = 0; i < cntr.size(); ++i) {
      // std::string word = cntr[i];
      if(cntr.at(i) == '&&') {
        andV.push_back(cntr.at(i));
        i++;
        // str1.replace(i,str1.length(),str2);
      }
  }

  std::cout << "\nAND VECTOR:" << std::endl;
  for(int i = 0; i < andV.size(); ++i) {
      std::cout << andV.at(i) << std::endl;
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
