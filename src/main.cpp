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

    std::string oldstr = "";
    std::cout << "$ ";
    std::getline(std::cin,oldstr);

    std::string str1 = oldstr.substr(0, oldstr.find("#", 0));

    std::vector<char*> check;

    if(str1 == "exit") {
        Exit *bye = new Exit();
        bye->execute(check);
    }

    Command* cmd = new Command(str1);
    cmd->setComVector(str1);
    cout << "\nCommands:" << endl;
    cmd->display();

    Connector* cntr = new Connector(NULL, NULL);
    cntr->setConVector(str1);
    cout << "\nConnectors:" << endl;
    cntr->display();

    AND* a = new AND(NULL, NULL);
    a->setANDVector(str1);
    cout << "\nAND:" << endl;
    a->display();

    OR* o = new OR(NULL, NULL);
    o->setORVector(str1);
    cout << "\nOR:" << endl;
    o->display();

    SEMICOLON* sc = new SEMICOLON(NULL, NULL);
    sc->setSEMIVector(str1);
    cout << "\nSEMICOLON:" << endl;
    sc->display();

    //
    // Exit* ex = new Exit();
    // ex->execute

    return 0;
}
