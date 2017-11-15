#ifndef TEST_H
#define TEST_H

#include "Base.h"
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Test : public Base {
 protected:
    char* flgPtr;
    string data;
    std::vector<std::string> flags;
    std::vector<char*> flgs;
    std::vector<string> tmpFlags;
    std::vector<char*> flgsVec;
    std::vector<char*> revFlg;
    std::string input;
 public:
    Test();
    Test(vector<char*>);
    string getData();
    void setTestVector(std::string);
    std::vector<char*> getTestVectorReversed();
    // virtual bool execute();
    void display();
};

#endif
