#include <iostream>
#include "Base.h"
#include "Command.h"

int main() {

    std::string input = "";
    std::cout << "$ ";
    std::getline(std::cin,input);
    // std::cout << input << std::endl;
    char *cstr = new char[input.length() + 1];
    strcpy(cstr, input.c_str());
    // std::cout << cstr << std::endl;
    Command* cmd = new Command();
    //std::cout << 1 << std::endl;
    cmd->setComVector(cstr);
    std::cout << "Contents of the Command Vector: " << std::endl;
    cmd->display();
    //std::cout << 3 << std::endl;
    return 0;
}
