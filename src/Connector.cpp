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
    using namespace std;
    using namespace boost;

using namespace std;

// std::vector<char*> connectors

// Constructor: takes a vector of char* and loads the connectors vector.
Connector::Connector(std::string input) {
    this->input = input;
}

// Takes in a char* and puts it into the vector of connectors.
void Connector::setConVector(std::string str1) {
  typedef vector< string > split_vector_type;

  split_vector_type cnts;
  split( cnts, str1, is_any_of(" "), token_compress_on );
  // commands.size() = coms.size();
  for(int i = 0; i < cnts.size(); ++i) {
      trim(cnts.at(i));
      connectors.push_back(cnts.at(i));
      // strcpy(commands.at(i), coms.at(i).c_str());
  }

  // for( std::vector<std::string>::iterator iter = connectors.begin(); iter != connectors.end(); ++iter )
  //   {
  //       if( *iter != ';' || *iter != '&' || *iter != '|' )
  //       {
  //           connectors.erase( iter );
  //       }
  //   }

  // for (string& str1 : connectors) {
  //     str1.erase(std::remove(str1.begin(), str1.end(), '|'), str1.end());
  // }

  std::cout << "\nConnectors Before: " << std::endl;
  for(unsigned i = 0; i < connectors.size(); ++i) {
      std::cout << connectors.at(i) << std::endl;
  }

  for( int i = 0; i < connectors.size(); ++i )
  {
    if( connectors.at(i) != ";" || connectors.at(i) != "&" || connectors.at(i) != "|" )
    {
        connectors.erase( connectors.begin() + i );
    }
  }

    cntr.reserve(connectors.size());
    for(int index = 0; index < connectors.size(); ++index) {
        cntr.push_back(connectors[index].c_str());
    }


    // string str1("abc-*-ABC-*-aBc");

    // Find all 'abc' substrings (ignoring the case)
    // Create a find_iterator
    // typedef find_iterator<string::iterator> string_find_iterator;
    // for(string_find_iterator It= make_find_iterator(str1, first_finder("abc", is_iequal())); It!=string_find_iterator(); ++It)
    // {
    //     connectors.push_back(copy_range<std::string>(*It)) << endl;
    // }

    // Output will be:
    // abc
    // ABC
    // aBC
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
