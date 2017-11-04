#include <iostream>
#include "Base.h"
#include "Command.h"

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
      std::cout << "Error: need more arguments." << std::endl;
      return 1;
    }

    std::string input = "";
    for(int i = 1; i < argc; ++i) {
      input.append(argv[i]);
    }
    std::cout << input << std::endl;
    // Command* cmd = new Command();
    // cmd->setComVector(input);
    // cmd->display();
    return 0;
}