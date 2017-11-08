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

// Default Constructor
Connector::Connector() {
    lhs = NULL;
    rhs = NULL;
}

// Constructor: Sets the left and right-hand sides of the connector.
Connector::Connector(Base* left, Base* right) {
    if(left != NULL) {
        lhs = left;
    } else if(right != NULL) {
        rhs = right;
    }
}

// Takes in a string and puts it into the vector of connectors.
void Connector::setConVector(std::string str1) {

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
        connectors.push_back(cnts.at(i));
    }

    for(unsigned i = 0; i < connectors.size(); ++i ) {
        if(connectors.at(i) == ";" || connectors.at(i) == "&&" || connectors.at(i) == "||") {
            tempContainer.push_back(connectors.at(i));
        }
    }

    cntr.reserve(tempContainer.size());
    for(unsigned index = 0; index < tempContainer.size(); ++index) {
        cntr.push_back((char*)tempContainer[index].c_str());
    }
}

std::vector<char*> Connector::getConVectorReversed() {
    // for(unsigned i = 0; i < cntr.size(); ++i) {
    //     revCntr.push_back(cntr.end());
    //     cntr.pop_back();
    // }
    revCntr = cntr;
    std::reverse(revCntr.begin(), revCntr.end());
    return revCntr;
}

// Displays all of the contents of the vector of connectors."
void Connector::display() {
    for(unsigned i = 0; i < cntr.size(); ++i) {
        std::cout << cntr.at(i) << std::endl;
    }
}