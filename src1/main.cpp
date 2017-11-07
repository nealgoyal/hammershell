#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "Parser.h"

#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

int main() {

    std::string str1 = "";
    std::cout << "$ ";
    std::getline(std::cin,str1);

    for(int i = 0; i < str1.length(); ++i) {
        if(str1.at(i) == ';') {
          str1.insert(i, " ");
          i++;
          // str1.replace(i,str1.length(),str2);
        }
    }

    //using boost to parse through the string
    typedef vector< string > split_vector_type;
    vector < string > temp;
    split_vector_type cnts;
    split( cnts, str1, is_any_of(" "), token_compress_on );
    for(int i = 0; i < cnts.size(); ++i) {
        temp.push_back(cnts.at(i));
    }

    //seperate vector into commands and connectors
    vector < string > commands;
    vector < string > connectors;
    for( int i = 0; i < temp.size(); ++i ) {
      if(temp.at(i) == ";" || temp.at(i) == "&&" || temp.at(i) == "||") {
          connectors.push_back(temp.at(i));
      }
      else {
          commands.push_back(temp.at(i));
      }
    }
    //convert temp from string to char
    vector < char* > finTemp;
    finTemp.reserve(temp.size());
    for(int index = 0; index < temp.size(); ++index) {
        finTemp.push_back((char*)temp[index].c_str());
    }

    //convert commands from string to char
    vector < char* > finCommands;
    finCommands.reserve(commands.size());
    for(int index = 0; index < commands.size(); ++index) {
        finCommands.push_back((char*)commands[index].c_str());
    }

    //convert connectors from string to char
    vector < char* > finConnectors;
    finConnectors.reserve(connectors.size());
    for(int index = 0; index < connectors.size(); ++index) {
        finConnectors.push_back((char*)connectors[index].c_str());
    }

    //displays

    //connectors
    cout << "\nConnectors: " << endl;
    for(int index = 0; index < finConnectors.size(); ++index) {
        cout << finConnectors[index] << endl;
    }

    //commands
    cout << "\nCommands: " << endl;
    for(int index = 0; index < finCommands.size(); ++index) {
        cout << finCommands[index] << endl;
    }

    cout << "\nOverall: " << endl;
    //overall
    for(int index = 0; index < finTemp.size(); ++index) {
        cout << finTemp[index] << endl;
    }

    //sys calls
    bool notGood = false;
    bool Good = true;
    Parser* p = new Parser(finTemp);
    char * arr[1024];

    for(int i = 0; i < finTemp.size(); ++i) {
        if(temp.at(i) == "||") {
            p->execute(finTemp);
            if(p->execute(finTemp) == Good) {
                p->execute(finTemp);
            }
        }
    }


    return 0;
}
