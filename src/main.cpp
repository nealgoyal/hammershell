#include <iostream>
#include <algorithm>
#include "Base.h"
#include "Command.h"
#include "Exit.h"
#include "Connector.h"
#include "AND.h"
#include "OR.h"
#include "SEMICOLON.h"

#include "InputRedirect.h"
#include "OutputRedirect.h"
#include "DoubleOutputRedirect.h"
#include "Pipe.h"

#include <boost/algorithm/string.hpp>
#include <vector>
using namespace std;
using namespace boost;

// Traverse and print the tree in inorder notation
// void displayTree() const;

Base* createTree(Base*, Connector* &, Command* &, std::string);

int main() {
    while(true) { // Prompts user again until they type exit.
        std::string oldstr1 = "";
        std::cout << "$ ";
        std::getline(std::cin, oldstr1);

        std::string str1 = oldstr1.substr(0, oldstr1.find("#", 0));
        if(str1 == "exit") {
            Exit *bye = new Exit();
            bye->execute();
        }

        int count = 0;
        //--------------------------------------------------------------------------------------------
        // checks if balanced parentheses. If not, throw error
        for(unsigned i = 0; i < str1.length(); ++i) {
            if(str1.at(i) == '(') {
                ++count;
            }
            if(str1.at(i) == ')') {
                ++count;
                if(count % 2 != 0) {
                    // perror("bash: syntax error near unexpected token ')'");
                    cout << "bash: syntax error near unexpected token ')'" << endl;
                    exit(1);
                }
            }
        }

        if(count % 2 != 0) {
            cout << "bash: syntax error near unexpected token '('" << endl;
            exit(1);
        }

        //Checks if we need to split string based on parentheses
        std::string rightString;
        if(str1.find('(') != std::string::npos) {
            std::size_t leftParenth = str1.find('(');
            std::size_t rightParenth = str1.rfind(')');
            rightString = str1.substr(leftParenth + 1, rightParenth - (leftParenth + 1));
            // cout << "Original string: " << str1 << endl;
            // cout << "Right String in Parentheses: " << rightString << endl;
            str1.erase(leftParenth, (rightParenth + 1) - leftParenth);
            // cout << "Original string after removal of parentheses: " << str1 << endl << endl;
        }

        // Runs if no parentheses
        if(rightString == "") {
            //--------------------------------------------------------------------------------------------
            //parsing for any [] -> test

            // Inserts "test " before the flag if there are brackets[]
            for(unsigned i = 0; i < str1.length(); ++i) {
                if(str1[i] == '-' && str1[i - 2] == '[') {
                    str1.insert(i, "test ");
                }
            }

            // Removes the brackets[] from the string
            vector<char> tester(str1.begin(), str1.end());
            for(unsigned i = 0; i < tester.size(); ++i) {
                if(tester.at(i) == '[') {
                    tester.erase(tester.begin() + i);
                    for(unsigned j = i + 1; j < tester.size(); ++j) {
                        if(tester.at(j) == ']') {
                            tester.erase(tester.begin() + j);
                        }
                    }
                }
            }
            // Now contains string as if test was used instead of brackets[]
            str1 = string(tester.begin(), tester.end());

            //--------------------------------------------------------------------------------------------

            // if(str1 == "exit") {
            //     Exit *bye = new Exit();
            //     bye->execute();
            // }
            Command* cmd = new Command();
            cmd->setComVector(str1);

            Connector* cntr = new Connector();
            cntr->setConVector(str1);

            //Turn these pointers into vectors
            std::vector<char*> connector = cntr->getConVectorReversed();
            std::vector<char*> command = cmd->getComVectorReversed();

            // Always initialize root to the first command
            Command* left = new Command(command);
            Base* root = left;
            command.pop_back();
            Connector* leftSide = NULL;

            std::string conType = "";
            std::string andStr = "&&";
            std::string orStr = "||";
            std::string semiStr = ";";

            std::string inpStr = "<";
            std::string outStr = ">";
            std::string doutStr = ">>";
            std::string pipeStr = "|";

            // Sets first connector when command is the lhs
            if(connector.size() != 0) {
                Command* right = new Command(command);
                command.pop_back();

                // Points at last c_string in connector
                conType = connector.back();
                connector.pop_back();
                // cout << "conType: " << conType << endl;

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
                } else if(conType == inpStr) {
                    InputRedirect* inpCon = new InputRedirect(left, right);
                    leftSide = inpCon;
                    root = inpCon;
                } else if(conType == outStr) {
                    OutputRedirect* outCon = new OutputRedirect(left, right);
                    leftSide = outCon;
                    root = outCon;
                } else if(conType == doutStr) {
                    DoubleOutputRedirect* doutCon = new DoubleOutputRedirect(left, right);
                    leftSide = doutCon;
                    root = doutCon;
                } else if(conType == pipeStr) {
                    Pipe* pipeCon = new Pipe(left, right);
                    leftSide = pipeCon;
                    root = pipeCon;
                }
            }

            // Populate tree with multiple connectors
            while(!connector.empty()) {
                Command* rightSide = new Command(command);
                command.pop_back();

                // Points at last c_string in connector vector
                conType = connector.back();
                connector.pop_back();

                // Checks which connector is passed in.
                // Sets lhs to connector and rhs to command(if it exists).
                root = createTree(root, leftSide, rightSide, conType);
            }
            root->execute();
        } else { // Runs if there are parentheses

        /************************Begin Solution for Exactly one Set of Parentheses************************/

            //--------------------------------------------------------------------------------------------
            //parsing for any [] -> test

            // Inserts "test " before the flag if there are brackets[]
            for(unsigned i = 0; i < str1.length(); ++i) {
                if(str1[i] == '-' && str1[i - 2] == '[') {
                    str1.insert(i, "test ");
                }
            }
            // Inserts "test " before the flag if there are brackets[]
            for(unsigned i = 0; i < rightString.length(); ++i) {
                if(rightString[i] == '-' && rightString[i - 2] == '[') {
                    rightString.insert(i, "test ");
                }
            }

            // Removes the brackets[] from the string
            vector<char> tester(str1.begin(), str1.end());
            for(unsigned i = 0; i < tester.size(); ++i) {
                if(tester.at(i) == '[') {
                    tester.erase(tester.begin() + i);
                    for(unsigned j = i + 1; j < tester.size(); ++j) {
                        if(tester.at(j) == ']') {
                            tester.erase(tester.begin() + j);
                        }
                    }
                }
            }
            // Now contains string as if test was used instead of brackets[]
            str1 = string(tester.begin(), tester.end());
            // Removes the brackets[] from the string
            vector<char> tester1(rightString.begin(), rightString.end());
            for(unsigned i = 0; i < tester1.size(); ++i) {
                if(tester1.at(i) == '[') {
                    tester1.erase(tester1.begin() + i);
                    for(unsigned j = i + 1; j < tester1.size(); ++j) {
                        if(tester1.at(j) == ']') {
                            tester1.erase(tester1.begin() + j);
                        }
                    }
                }
            }
            // Now contains string as if test was used instead of brackets[]
            rightString = string(tester1.begin(), tester1.end());

            //--------------------------------------------------------------------------------------------

            // if(str1 == "exit") {
            //     Exit *bye = new Exit();
            //     bye->execute();
            // }

            Command* cmd = new Command();
            Command* cmd1 = new Command();
            cmd->setComVector(str1);
            cmd1->setComVector(rightString);

            Connector* cntr = new Connector();
            Connector* cntr1 = new Connector();
            cntr->setConVector(str1);
            cntr1->setConVector(rightString);

            //Turn these pointers into vectors
            std::vector<char*> connector = cntr->getConVector(); // Leave original to take the last connector in str1
            std::vector<char*> command = cmd->getComVectorReversed();
            //Turn these pointers into vectors
            std::vector<char*> connector1 = cntr1->getConVectorReversed();
            std::vector<char*> command1 = cmd1->getComVectorReversed();

            //*****************IMPORTANT*******************//

            std::string conType = "";
            std::string conType1 = "";
            std::string lastConType = "";
            std::string andStr = "&&";
            std::string orStr = "||";
            std::string semiStr = ";";

            std::string inpStr = "<";
            std::string outStr = ">";
            std::string doutStr = ">>";
            std::string pipeStr = "|";

            // Sets first connector when command is the lhs
            if(connector.size() != 0) { // NEED TO REMOVE LAST CONNECTOR FROM STRING 1
                // Points at last c_string in connector
                lastConType = connector.back();
                connector.pop_back();
            }
            std::reverse(connector.begin(), connector.end()); // Reverse connector vector for uses later

            // Always initialize root to the first command
            Command* left = new Command(command);
            Command* left1 = new Command(command1);
            Base* root = NULL; // Root pointer to top connector
            Base* leftTree = left; // Root pointer to left tree
            Base* rightTree = left1; // Root pointer to right tree
            command.pop_back();
            command1.pop_back();
            Connector* leftSide = NULL;
            Connector* leftSide1 = NULL;

            // Sets first connector when command is the lhs
            if(connector.size() != 0) {
                Command* right = new Command(command);
                command.pop_back();

                // Points at last c_string in connector
                conType = connector.back();
                connector.pop_back();
                // cout << "conType: " << conType << endl;

                // Checks which connector is passed in.
                // Sets lhs to command and rhs to command(if it exists).
                if(conType == semiStr) {
                    SEMICOLON* semiCon = new SEMICOLON(left, right);
                    leftSide = semiCon;
                    leftTree = semiCon;
                } else if(conType == andStr) {
                    AND* andCon = new AND(left, right);
                    leftSide = andCon;
                    leftTree = andCon;
                } else if(conType == orStr) {
                    OR* orCon = new OR(left, right);
                    leftSide = orCon;
                    leftTree = orCon;
                } else if(conType == inpStr) {
                    InputRedirect* inpCon = new InputRedirect(left, right);
                    leftSide = inpCon;
                    leftTree = inpCon;
                } else if(conType == outStr) {
                    OutputRedirect* outCon = new OutputRedirect(left, right);
                    leftSide = outCon;
                    leftTree = outCon;
                } else if(conType == doutStr) {
                    DoubleOutputRedirect* doutCon = new DoubleOutputRedirect(left, right);
                    leftSide = doutCon;
                    leftTree = doutCon;
                } else if(conType == pipeStr) {
                    Pipe* pipeCon = new Pipe(left, right);
                    leftSide = pipeCon;
                    leftTree = pipeCon;
                }
            }
            // Sets first connector when command is the lhs
            if(connector1.size() != 0) {
                Command* right1 = new Command(command1);
                command1.pop_back();

                // Points at last c_string in connector
                conType1 = connector1.back();
                connector1.pop_back();
                // cout << "conType: " << conType << endl;

                // Checks which connector is passed in.
                // Sets lhs to command and rhs to command(if it exists).
                if(conType1 == semiStr) {
                    SEMICOLON* semiCon1 = new SEMICOLON(left1, right1);
                    leftSide1 = semiCon1;
                    rightTree = semiCon1;
                } else if(conType1 == andStr) {
                    AND* andCon1 = new AND(left1, right1);
                    leftSide1 = andCon1;
                    rightTree = andCon1;
                } else if(conType1 == orStr) {
                    OR* orCon1 = new OR(left1, right1);
                    leftSide1 = orCon1;
                    rightTree = orCon1;
                } else if(conType1 == inpStr) {
                    InputRedirect* inpCon1 = new InputRedirect(left1, right1);
                    leftSide = inpCon1;
                    root = inpCon1;
                } else if(conType1 == outStr) {
                    OutputRedirect* outCon1 = new OutputRedirect(left1, right1);
                    leftSide = outCon1;
                    root = outCon1;
                } else if(conType1 == doutStr) {
                    DoubleOutputRedirect* doutCon1 = new DoubleOutputRedirect(left1, right1);
                    leftSide = doutCon1;
                    root = doutCon1;
                } else if(conType1 == pipeStr) {
                    Pipe* pipeCon1 = new Pipe(left1, right1);
                    leftSide = pipeCon1;
                    root = pipeCon1;
                }
            }

            // Populate tree with multiple connectors
            while(!connector.empty()) {
                Command* rightSide = new Command(command);
                command.pop_back();

                // Points at last c_string in connector vector
                conType = connector.back();
                connector.pop_back();

                // Checks which connector is passed in.
                // Sets lhs to connector and rhs to command(if it exists).
                leftTree = createTree(leftTree, leftSide, rightSide, conType);
            }
            // Populate tree with multiple connectors
            while(!connector.empty()) {
                Command* rightSide1 = new Command(command1);
                command1.pop_back();

                // Points at last c_string in connector vector
                conType1 = connector1.back();
                connector1.pop_back();

                // Checks which connector is passed in.
                // Sets lhs to connector and rhs to command(if it exists).
                rightTree = createTree(rightTree, leftSide1, rightSide1, conType1);
            }

            // Finally, discover the last connector and create a new root from it
            // Checks which connector is passed in.
            if(lastConType == semiStr) {
                SEMICOLON* semiCon = new SEMICOLON(leftTree, rightTree);
                root = semiCon;
            } else if(lastConType == andStr) {
                AND* andCon = new AND(leftTree, rightTree);
                root = andCon;
            } else if(lastConType == orStr) {
                OR* orCon = new OR(leftTree, rightTree);
                root = orCon;
            }  else if(lastConType == inpStr) {
                InputRedirect* inpCon = new InputRedirect(leftTree, rightTree);
                root = inpCon;
            } else if(lastConType == outStr) {
                OutputRedirect* outCon = new OutputRedirect(leftTree, rightTree);
                root = outCon;
            } else if(lastConType == doutStr) {
                DoubleOutputRedirect* doutCon = new DoubleOutputRedirect(leftTree, rightTree);
                root = doutCon;
            } else if(lastConType == pipeStr) {
                Pipe* pipeCon = new Pipe(leftTree, rightTree);
                root = pipeCon;
            }
            root->execute();
        }
        // root->execute();
    }
    return 0;
}

// Creates a tree and returns the root of the tree.
Base* createTree(Base* root, Connector* &left, Command* &right, std::string conType) {
    // Comparisons for strings
    std::string andStr = "&&";
    std::string orStr = "||";
    std::string semiStr = ";";

    if(conType == semiStr) {
        SEMICOLON* semiCon = new SEMICOLON(left, right);
        left = semiCon;
        root = semiCon;
    } else if(conType == andStr) {
        AND* andCon = new AND(left, right);
        left = andCon;
        root = andCon;
    } else if(conType == orStr) {
        OR* orCon = new OR(left, right);
        left = orCon;
        root = orCon;
    }
    return root;
}
