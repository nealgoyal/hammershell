#include "Connector.h"
#include "string.h"
#include <vector>
#include <iostream>

// std::vector<char*> connectors

// Constructor: takes a vector of char* and loads the connectors vector.
Connector::Connector(std::string input) {
    this->input = input;
}

// Takes in a char* and puts it into the vector of connectors.
void Connector::setConVector(std::string str1) {
    // char delim[] = " `1234567890-=~!@#$%^*()_+qwertyuiop[]QWERTYUIOP{}asdfghjkl'ASDFGHJKL:zxcvbnm,./ZXCVBNM<>?";
    // char *token = strtok(input,delim);
    // connectors.push_back(token);

    // string str1("abc-*-ABC-*-aBc");

    // Find all 'abc' substrings (ignoring the case)
    // Create a find_iterator
    typedef find_iterator<string::iterator> string_find_iterator;
    for(string_find_iterator It= make_find_iterator(str1, first_finder("abc", is_iequal())); It!=string_find_iterator(); ++It)
    {
        connectors.push_back(copy_range<std::string>(*It) << endl;
    }

    // Output will be:
    // abc
    // ABC
    // aBC
}

// Displays all of the contents of the vector of connectors."
void Connector::display() {
    for(unsigned i = 0; i < connectors.size(); ++i) {
        std::cout << connectors.at(i) << std::endl;
    }
}
