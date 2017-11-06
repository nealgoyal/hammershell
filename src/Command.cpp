#include "Command.h"

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
//  protected:
//     vector<char*> commands;
//  public:

// Constructor: takes a vector of char* and loads the commands vector.
Command::Command(std::string input) {
    // commands = input;
    this->input = input;
}

// Takes in a char* and puts it into the vector of commands.
void Command::setComVector(std::string str1) {

  replace(str1.begin(), str1.end(), '&', '!');
  replace(str1.begin(), str1.end(), '|', '!');
  replace(str1.begin(), str1.end(), ';', '!');

  // cout << str1 << endl;

  typedef vector< string > split_vector_type;

  split_vector_type coms;
  split( coms, str1, is_any_of("!"), token_compress_on );
  // commands.size() = coms.size();
  for(int i = 0; i < coms.size(); ++i) {
      trim(coms.at(i));
      commands.push_back(coms.at(i));
      // strcpy(commands.at(i), coms.at(i).c_str());
  }


  cmds.reserve(commands.size());
  for(int index = 0; index < commands.size(); ++index) {
      cmds.push_back((char*)commands[index].c_str());
      // cmds[index] = (char*)commands[index].c_str();
      cout << cmds[index] << endl;
  }
<<<<<<< HEAD

  display();

  if(!execute(cmds)) {
    cout << "NO";
  }
  else {
    cout << "YES";
=======
  
  // Populates vector of char* for execute
  for(int i = 0; i < commands.size(); ++i) {
      exCmd[i] = &commands[i][0];
>>>>>>> d017cb89c538326fd2381bac0f279ced38e5fb68
  }
}

bool Command::execute(std::vector<char*> exCmd) {
    pid_t pid = fork(); // Creates child process through fork
    if(pid == 0) { // Child Process
<<<<<<< HEAD
        // cout << "ENTERED CHILD" << endl;
        cout << cmd[0] << " " << cmd[1] << endl;
        if(execvp(cmd[0], cmd.data()) == -1) {
            // cout << "ENTERED EXEC" << endl;
=======
        if(execvp(exCmd[0], exCmd.data()) == -1) {
>>>>>>> d017cb89c538326fd2381bac0f279ced38e5fb68
            perror("Failed to Execute");
            return false;
        }
    } else if(pid > 0) { // Parent Process
        // cout << "ENTERED PID" << endl;
        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) == 1) {
            // cout << "ENTERED STAT" << endl;
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

// Displays all of the contents of the vector of commands.
void Command::display() {
  for(int i = 0; i < cmds.size(); ++i) {
      std::cout << cmds.at(i) << std::endl;
  }
    //std::cout << commands.at(0) << std::endl;
    //std::cout << commands.at(1) << std::endl;
    //std::cout << commands.at(2) << std::endl;
}
