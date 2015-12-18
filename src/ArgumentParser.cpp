#include <ArgumentParser/ArgumentParser.hpp>
#include <iostream>

namespace ArgumentParser {

    bool isSuccess(ArgumentParser::Status status) {
        return ArgumentParser::StatusOk == status;
    }

    bool isPartial(ArgumentParser::Status status) {
        return ArgumentParser::StatusQuoteSingle == status || ArgumentParser::StatusQuoteDouble == status;
    }

    bool isError(ArgumentParser::Status status) {
        return ArgumentParser::ErrorEscapeSequenceInvalid == status ||
            ArgumentParser::ErrorSingleUnterminated == status ||
            ArgumentParser::ErrorDoubleUnterminated == status;
    }

    ArgumentParser::ArgumentParser() : status_(StatusOk) {}

    ArgumentParser::Status ArgumentParser::parse(Arguments &args, const std::string& line) {
        current_ = "";
        status_ = StatusOk;
        return continueParsing(args, line, status_);
    }

    ArgumentParser::Status ArgumentParser::continueParsing(Arguments& args, const std::string& line, Status status) {
        status_ = status;

        std::string::size_type i = 0;
        if (StatusOk == status_) {
            return parseArray(args, line);
        } else if (StatusQuoteSingle == status_) {
            return continueQuote(args, line, '\'', StatusQuoteSingle, i);
        } else if (StatusQuoteDouble == status_) {
            return continueQuote(args, line, '"', StatusQuoteDouble, i);
        } else {
            return status_;
        }
    }

    ArgumentParser::Status ArgumentParser::continueQuote(Arguments& args, const std::string& line, char delim, Status continueStatus, std::string::size_type& i) {
        for (std::string::size_type l = line.length(); i < l; ++i) {
            char c = line[i];
            if (delim == c) {
                args.push_back(current_);
                current_ = "";
                status_ = StatusOk;
                return status_;
            } else if ('\\' == c) {
                if (i < l - 1) {
                    char n = line[i + 1];
                    if ('\\' == n || delim == n) {
                        current_ += n;
                        ++i;
                    } else {
                        status_ = ErrorEscapeSequenceInvalid;
                        return status_;
                    }
                } else {
                    status_ = ErrorSingleUnterminated;
                    return status_;
                }
            } else {
                current_ += c;
            }
        }

        current_ += "\n";
        status_ = continueStatus;
        return status_;
    }

    ArgumentParser::Status ArgumentParser::parseArray(Arguments& args, const std::string& line) {
        for (std::string::size_type i = 0, l = line.length(); i < l; ++i) {
            char c = line[i];
            if (std::isspace(c)) {
                if (current_.size()) {
                    args.push_back(current_);
                    current_ = "";
                }
            } else if ('"' == c) {
                ++i;
                continueQuote(args, line, '"', StatusQuoteDouble, i);
            } else if ('\'' == c) {
                ++i;
                continueQuote(args, line, '\'', StatusQuoteSingle, i);
            } else {
                current_ += c;
            }
        }
        
        if (StatusOk == status_ && current_.length()) {
            args.push_back(current_);
            current_ = "";
        }

        return status_;
    }

}
