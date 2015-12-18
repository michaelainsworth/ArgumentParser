#ifndef AUTOMATICARGUMENTPARSER_HPP
#define AUTOMATICARGUMENTPARSER_HPP

#include <ArgumentParser/ArgumentParser.hpp>
#include <iostream>

namespace ArgumentParser {

    class AutomaticArgumentParser {
    public:
        
        AutomaticArgumentParser();
        AutomaticArgumentParser(const std::string& initialPrompt, const std::string& continueSinglePrompt, const std::string& continueDoublePrompt);

        ArgumentParser::Arguments parse(std::istream& ins, std::ostream& outs);

    private:

        std::string prompt(ArgumentParser::Status status);

        std::string initialPrompt_, continueSinglePrompt_, continueDoublePrompt_;
        
    };

}

#endif // #ifndef AUTOMATICARGUMENTPARSER_HPP
