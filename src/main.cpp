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

void createTree(vector<string> &);

int main() {

    std::string oldstr = "";
    std::cout << "$ ";
    std::getline(std::cin,oldstr);

    std::string str1 = oldstr.substr(0, oldstr.find("#", 0));

    std::vector<char*> check;
    //Base* root = NULL;
    //Base* left = NULL;
    //Base* right = NULL;

    if(str1 == "exit") {
        Exit *bye = new Exit();
        bye->execute(check);
    }

    Command* cmd = new Command(str1);
    cmd->setComVector(str1);
    cout << "\nCommands:" << endl;
    cmd->display();

    Connector* cntr = new Connector();
    cntr->setConVector(str1);
    cout << "\nConnectors:" << endl;
    cntr->display();

    //Turn these pointers into vectors
    std::vector<char*> connector = cntr->getConVector();
    std::vector<char*> command = cmd->getComVector();

    //cout << "\nConnector Vector: " << endl;
    //for(unsigned i = 0; i < connector.size(); ++i) {
    //    std::cout << connector.at(i) << ", ";
    //}
    //std::cout << std::endl;
    
    //Convert into type Base*
    // std::vector<Base*> conTree;
    // std::vector<char*>::iterator it;
    // for(it == connector.begin(); it != connector.end(); ++it) {
    //     conTree.push_back(dynamic_cast<Base*>(*it));
    // }

    // Populates a basic tree
    // if(connector.size() == 1) {
    //     // Grab the last two commands
    //     right = command.back();
    //     command.pop_back();
    //     left = command.back();
    //     command.pop_back();

    //     char* conType = connector.back();
    //     connector.pop_back();

    //     if(conType == ";") {
    //         SEMICOLON* newCon = new SEMICOLON(lhs, rhs);
    //         root = newCon;
    //     } else if(conType == "&&") {
    //         AND* newCon = new AND(lhs, rhs);
    //         root = newCon;
    //     } else if(conType == "||") {
    //         OR* newCon = new OR(lhs, rhs);
    //         root = newCon;
    //     }
    // }

    //Populate a tree using cntr and cmd vectors.
    // cout << "\nCreate a tree: " << endl;
    // cout << "Connector back: " << connector.back();
    // root = cntr;
    // cout << root.back(); << endl;
    // cout << root << " ";
    // cout << *root;

    AND* a = new AND();
    a->setANDVector(str1);
    cout << "\nAND:" << endl;
    a->display();

    OR* o = new OR();
    o->setORVector(str1);
    cout << "\nOR:" << endl;
    o->display();

    SEMICOLON* sc = new SEMICOLON();
    sc->setSEMIVector(str1);
    cout << "\nSEMICOLON:" << endl;
    sc->display();

    return 0;
}
