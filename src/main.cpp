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


int main() {
    while(true) { // Prompts user again until they type exit.
        std::string oldstr = "";
        std::cout << "$ ";
        std::getline(std::cin, oldstr);
    
        std::string str1 = oldstr.substr(0, oldstr.find("#", 0));
    
        std::vector<char*> check;
    
        if(str1 == "exit") {
            Exit *bye = new Exit();
            bye->execute(check);
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
    
        cout << "\nCommand Vector Reversed before pop: " << endl;
        for(unsigned i = 0; i < command.size(); ++i) {
           std::cout << command.at(i) << " ";
        }
        std::cout << std::endl;

        cout << "\nConnector Vector Reversed: " << endl;
        for(unsigned i = 0; i < connector.size(); ++i) {
           std::cout << connector.at(i) << " ";
        }
        std::cout << std::endl;
        
        // std::cout << "First command: " << command.at(0) << std::endl;
        // Always initialize root to the first command
        Command* left = new Command(command);
        Base* root = left;
        std::cout << "First command: " << left->getData() << endl;
        command.pop_back();

        // Comparisons for strings
        std::string conType = "";
        std::string andStr = "&&";
        std::string orStr = "||";
        std::string semiStr = ";";

        cout << "Initial root: " << root << endl;

        // Populate the tree
        for(unsigned i = 0; i < connector.size(); ++i) {
            Command* right = new Command(command);
            std::cout << "Second command: " << right->getData() << endl;
            command.pop_back();
            // Base* root = NULL; // = left;

            conType = connector.back();
            connector.pop_back();
            cout << "conType: " << conType << endl;
            if(conType == semiStr) {
                SEMICOLON* semiCon = new SEMICOLON(left, right);
                root = semiCon;
            } else if(conType == andStr) {
                AND* andCon = new AND(left, right);
                root = andCon;
            } else if(conType == orStr) {
                OR* orCon = new OR(left, right);
                root = orCon;
            }
        }

        // AND* a = new AND();
        // a->setANDVector(str1);
        // cout << "\nAND:" << endl;
        // a->display();
    
        // OR* o = new OR();
        // o->setORVector(str1);
        // cout << "\nOR:" << endl;
        // o->display();
    
        // SEMICOLON* sc = new SEMICOLON();
        // sc->setSEMIVector(str1);
        // cout << "\nSEMICOLON:" << endl;
        // sc->display();

        // std::cout << "Temp value: " << temp->getData() << std::endl;
        // Base* root = temp;
        // std::cout << "Root: " << *root << std::endl;
        // Populates a tree that stores both vectors and commands
        // if(connector.size() == 0) {
        //     root = cmd;
        // }
        // for(unsigned i = 0; i < connector.size(); ++i) {
        
    
        // }
    
        //Populate a tree using cntr and cmd vectors.
        // cout << "\nCreate a tree: " << endl;
        // cout << "Connector back: " << connector.back();
        // root = cntr;
        // cout << root.back(); << endl;
        // cout << root << " ";
        // cout << *root;
    }
    return 0;
}