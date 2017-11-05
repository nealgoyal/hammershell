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

    replace(str1.begin(), str1.end(), '&', '!');
    replace(str1.begin(), str1.end(), '|', '!');
    replace(str1.begin(), str1.end(), ';', '!');

    cout << str1 << endl;

    typedef vector< string > split_vector_type;

    split_vector_type SplitVec; // #2: Search for tokens
    split( SplitVec, str1, is_any_of("!"), token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    for(int i = 0; i < SplitVec.size(); ++i) {
        trim(SplitVec.at(i));
        std::cout << SplitVec.at(i) << std::endl;
    }

    return 0;
}
