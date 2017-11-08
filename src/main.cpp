#include <iostream>
#include <algorithm>
#include "Base.h"
#include "Command.h"
#include "Exit.h"
#include "Connector.h"
#include "AND.h"
#include "OR.h"
#include "SEMICOLON.h"

#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

// Traverse and print the tree in inorder notation
// void displayTree() const;

int main() {
    while(true) { // Prompts user again until they type exit.
        std::string oldstr = "";
        std::cout << "$ ";
        std::getline(std::cin, oldstr);
    
        std::string str1 = oldstr.substr(0, oldstr.find("#", 0));
    
        if(str1 == "exit") {
            Exit *bye = new Exit();
            bye->execute();
        }
    
        Command* cmd = new Command();
        cmd->setComVector(str1);
        cout << "\nCommands:" << endl;
        cmd->display();
    
        Connector* cntr = new Connector();
        cntr->setConVector(str1);
        cout << "\nConnectors:" << endl;
        cntr->display();
    
        //Turn these pointers into vectors
        std::vector<char*> connector = cntr->getConVectorReversed();
        std::vector<char*> command = cmd->getComVectorReversed();
    
        // For testing
        // cout << "\nCommand Vector Reversed before pop: " << endl;
        // for(unsigned i = 0; i < command.size(); ++i) {
        //    std::cout << command.at(i) << " ";
        // }
        // std::cout << std::endl;

        // cout << "\nConnector Vector Reversed: " << endl;
        // for(unsigned i = 0; i < connector.size(); ++i) {
        //    std::cout << connector.at(i) << " ";
        // }
        // std::cout << std::endl;
        
        // std::cout << "First command: " << command.at(0) << std::endl;
        // Always initialize root to the first command
        Command* left = new Command(command);
        Base* root = left;
        std::cout << "Command 1: " << left->getData() << endl;
        command.pop_back();
        Connector* leftSide = NULL;

        // Comparisons for strings
        std::string conType = "";
        std::string andStr = "&&";
        std::string orStr = "||";
        std::string semiStr = ";";

        cout << "Initial root: " << root << endl;

        // Sets first connector when command is the lhs
        if(connector.size() != 0) {
            Command* right = new Command(command);
            std::cout << "Command 2: " << right->getData() << endl;
            command.pop_back();
            
            // Points at last c_string in connector
            conType = connector.back();
            connector.pop_back();
            cout << "conType: " << conType << endl;

            // Checks which connector is passed in.
            // Sets lhs to command and rhs to command(if it exists).
            if(conType == semiStr) {
                SEMICOLON* semiCon = new SEMICOLON(left, right);
                leftSide = semiCon;
                root = semiCon;
            } else if(conType == andStr) {
                AND* andCon = new AND(left, right);
                leftSide = andCon;
                root = andCon;
            } else if(conType == orStr) {
                OR* orCon = new OR(left, right);
                leftSide = orCon;
                root = orCon;
            }
        }

        // Populate tree with multiple connectors
        while(!connector.empty()) {
            Command* rightSide = new Command(command);
            // std::cout << "Next Command " << ": " << rightSide->getData() << endl;
            command.pop_back();
            
            // Points at last c_string in connector vector
            conType = connector.back();
            connector.pop_back();
            cout << "conType: " << conType << endl;

            // Checks which connector is passed in.
            // Sets lhs to connector and rhs to command(if it exists).
            if(conType == semiStr) {
                SEMICOLON* semiCon = new SEMICOLON(leftSide, rightSide);
                leftSide = semiCon;
                root = semiCon;
            } else if(conType == andStr) {
                AND* andCon = new AND(leftSide, rightSide);
                leftSide = andCon;
                root = andCon;
            } else if(conType == orStr) {
                OR* orCon = new OR(leftSide, rightSide);
                leftSide = orCon;
                root = orCon;
            }
        }
    }
    return 0;
}