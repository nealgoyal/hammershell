#include <iostream>
#include <algorithm>
#include "Base.h"
#include "Command.h"

#include <boost/algorithm/string.hpp>
    using namespace std;
    using namespace boost;

int main() {

    std::string str1 = "";
    std::cout << "$ ";
    std::getline(std::cin,str1);
    
    Command* cmd = new Command(str1);
    cmd->setComVector(str1);


    return 0;
}
