#include <ArgumentParser/AutomaticArgumentParser.hpp>
#include <iostream>

bool delegate(const ArgumentParser::ArgumentParser::Arguments& args);
void help();

int main(int argc, const char** argv) {
    ArgumentParser::AutomaticArgumentParser parser;
    ArgumentParser::ArgumentParser::Status status = ArgumentParser::ArgumentParser::StatusOk;

    bool run = true;
    while (run && std::cin) {
        ArgumentParser::ArgumentParser::Arguments args = parser.parse(std::cin, std::cout);
        run = delegate(args);
    }

    return 0;
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
            std::cout << (1 == i ? "" : " ") << *it;
            ++i;
        }

        std::cout << std::endl;
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
