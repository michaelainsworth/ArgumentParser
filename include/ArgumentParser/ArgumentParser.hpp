#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <string>
#include <vector>

namespace ArgumentParser {

    class ArgumentParser {
    public:
        
        typedef std::vector<std::string> Arguments;
        
        enum Status {
            StatusOk = 0,
            StatusQuoteSingle,
            StatusQuoteDouble,

            ErrorEscapeSequenceInvalid,
            ErrorSingleUnterminated,
            ErrorDoubleUnterminated
        };
        
        ArgumentParser();

        Status parse(Arguments& args, const std::string& line);
        Status continueParsing(Arguments& args, const std::string& line, Status status);

    private:

        Status parseArray(Arguments& args, const std::string& line);
        Status continueQuote(Arguments& args, const std::string& line, char delim, Status continueStatus, std::string::size_type& i);

        Status status_;
        std::string current_;
        
    };

    bool isSuccess(ArgumentParser::Status status);
    bool isPartial(ArgumentParser::Status status);
    bool isError(ArgumentParser::Status status);

}

#endif // #ifndef ARGUMENTPARSER_HPP
