#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>

using namespace std;

class Parser {
private:
  vector < char* > inp;
 public:
    Parser ();
    Parser (vector < string > );

    bool execute(char *);
};

#endif
