#include <iostream>
#include <algorithm>
#include "Base.h"
#include "Command.h"
#include "Connector.h"
#include "AND.h"
#include "OR.h"
#include "SEMICOLON.h"


#include <boost/algorithm/string.hpp>
    using namespace std;
    using namespace boost;

int main() {

    std::string str1 = "";
    std::cout << "$ ";
    std::getline(std::cin,str1);

    Command* cmd = new Command(str1);
    cmd->setComVector(str1);
    cout << "\nCommands:" << endl;
    cmd->display();

    Connector* cntr = new Connector(str1);
    cntr->setConVector(str1);
    cout << "\nConnectors:" << endl;
    cntr->display();

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

    //
    // Exit* ex = new Exit();
    // ex->execute

    return 0;
}
