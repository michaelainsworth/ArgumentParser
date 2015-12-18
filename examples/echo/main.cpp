#include <ArgumentParser/ArgumentParser.hpp>
#include <iostream>

void help();

int main(int argc, const char** argv) {
    ArgumentParser::ArgumentParser parser;
    ArgumentParser::ArgumentParser::Status status = ArgumentParser::ArgumentParser::StatusOk;

    while (ArgumentParser::ArgumentParser::StatusOk == status) {
        std::string command;
        ArgumentParser::ArgumentParser::Arguments args;

        status = parser.getArguments(command, args);
        if ("help" == command) {
            help();
        } else if ("quit" == command) {
            break;
        } else if ("echo" == command) {
            ArgumentParser::ArgumentParser::Arguments::iterator it = args.begin(),
                end = args.end();

            int i = 1;
            for (; it != end; ++it) {
                std::cout << "Argument " << i << ": " << *it << std::endl;
                ++i;
            }
        } else {
            help();
        }
    }

    return 1;
}

void help() {
    std::cout <<
    "Options\n"
    "help       Print this help message.\n"
    "echo       Echo each argument, one per line.\n"
    "quit       Exit the program." <<
    std::endl;
}
