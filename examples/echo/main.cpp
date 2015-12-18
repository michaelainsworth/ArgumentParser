#include <ArgumentParser/ArgumentParser.hpp>
#include <iostream>

std::string prompt(ArgumentParser::ArgumentParser::Status status);
bool delegate(const ArgumentParser::ArgumentParser::Arguments& args);
void help();

int main(int argc, const char** argv) {
    ArgumentParser::ArgumentParser parser;
    ArgumentParser::ArgumentParser::Status status = ArgumentParser::ArgumentParser::StatusOk;

    ArgumentParser::ArgumentParser::Arguments args;
    bool run = true;
    while (run) {
        std::cout << prompt(status);

        std::string line;
        std::getline(std::cin, line);
        if (!std::cin) {
            break;
        }

        args.clear();
        status = parser.parse(args, line);

        if (ArgumentParser::isSuccess(status)) {
            run = delegate(args);
        } else if (ArgumentParser::isPartial(status)) {
            while (ArgumentParser::isPartial(status)) {
                std::cout << prompt(status);

                std::getline(std::cin, line);
                if (!std::cin) {
                    break;
                }

                status = parser.continueParsing(args, line, status);
            }

            if (ArgumentParser::isSuccess(status)) {
                run = delegate(args);
            } else if (ArgumentParser::isPartial(status)) {
                // TODO: Proper error.
                std::cerr << "Partial arguments before end of input." << std::endl;
            } else {
                std::cerr << "Error parsing arguments." << std::endl;
            }
        } else if (ArgumentParser::isError(status)) {
            std::cerr << "Error parsing arguments." << std::endl;
        }
    }

    return 0;
}

std::string prompt(ArgumentParser::ArgumentParser::Status status) {
    std::string p("=> ");
    switch (status) {
        case ArgumentParser::ArgumentParser::StatusQuoteSingle:
            p = "'> ";
            break;
        case ArgumentParser::ArgumentParser::StatusQuoteDouble:
            p = "\"> ";
            break;
    }
    return p;
}

bool delegate(const ArgumentParser::ArgumentParser::Arguments& args) {
    if (!args.size()) {
        return true;
    }

    std::string command = args[0];
    if ("help" == command) {
        help();
    } else if ("quit" == command) {
        return false;
    } else if ("echo" == command) {
        ArgumentParser::ArgumentParser::Arguments::const_iterator it = args.begin(),
            end = args.end();

        int i = 1;
        for (++it != end; it != end; ++it) {
            std::cout << "   argument " << i << ": " << *it << std::endl;
            ++i;
        }
    } else {
        help();
    }

    return true;
}

void help() {
    std::cout <<
    "Options\n"
    "help       Print this help message.\n"
    "echo       Echo each argument, one per line.\n"
    "quit       Exit the program." <<
    std::endl;
}
