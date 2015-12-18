#include <ArgumentParser/AutomaticArgumentParser.hpp>

namespace ArgumentParser {

    AutomaticArgumentParser::AutomaticArgumentParser() : initialPrompt_("=> "), continueSinglePrompt_("'> "), continueDoublePrompt_("\"> ") {}

    AutomaticArgumentParser::AutomaticArgumentParser(const std::string& initialPrompt, const std::string& continueSinglePrompt, const std::string& continueDoublePrompt)
    : initialPrompt_(initialPrompt), continueSinglePrompt_(continueSinglePrompt), continueDoublePrompt_(continueDoublePrompt) {}

    ArgumentParser::Arguments AutomaticArgumentParser::parse(std::istream& ins, std::ostream& outs) {
        ArgumentParser parser;
        ArgumentParser::Status status = ArgumentParser::StatusOk;
        ArgumentParser::Arguments args;

        std::cout << prompt(status);

        std::string line;
        if (!std::getline(ins, line)) {
            return args;
        }

        status = parser.parse(args, line);

        if (isSuccess(status)) {
            return args;
        } else if (isPartial(status)) {
            while (isPartial(status)) {
                outs << prompt(status);

                std::getline(ins, line);
                if (!ins) {
                    break;
                }

                status = parser.continueParsing(args, line, status);
            }

            if (isSuccess(status)) {
                return args;
            } else if (isPartial(status)) {
                outs << "Partial arguments before end of input." << std::endl;
            } else {
                outs << "Error parsing arguments." << std::endl;
            }
        } else if (isError(status)) {
            outs << "Error parsing arguments." << std::endl;
        }

        // TODO: Return errors?
    }

    std::string AutomaticArgumentParser::prompt(ArgumentParser::Status status) {
        if (ArgumentParser::ArgumentParser::StatusQuoteSingle == status) {
            return continueSinglePrompt_;
        } else if (ArgumentParser::ArgumentParser::StatusQuoteDouble == status) {
            return continueDoublePrompt_;
        } else {
            return initialPrompt_;
        }
    }

}
