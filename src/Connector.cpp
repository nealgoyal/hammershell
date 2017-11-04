#include "Connector.h"
#include "string.h"
#include <vector>
#include <iostream>

// std::vector<char*> connectors

// Constructor: takes a vector of char* and loads the connectors vector.
Connector::Connector(std::vector<char*> input) {
    connectors = input;
}

// Takes in a char* and puts it into the vector of connectors.
void Connector::setConVector(char* input) {
    char delim[] = " `1234567890-=~!@#$%^*()_+qwertyuiop[]QWERTYUIOP{}asdfghjkl'ASDFGHJKL:zxcvbnm,./ZXCVBNM<>?";
    char *token = strtok(input,delim);
    connectors.push_back(token);    
}

// Displays all of the contents of the vector of connectors."
void Connector::display() {
    for(int i = 0; i < connectors.size(); ++i) {
        std::cout << connectors.at(i) << std::endl;
    }
}
