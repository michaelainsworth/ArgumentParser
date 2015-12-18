#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <iostream>
#include <string>
#include <vector>

class ArgumentParser {
public:
    
    typedef std::vector<std::string> Arguments;
    
    enum Status {
        StatusOk,
        StatusError,
        StatusEnd
    };
    
    Status getArguments(std::string& first, Arguments& args);
    
};

#endif // #ifndef ARGUMENTPARSER_HPP
