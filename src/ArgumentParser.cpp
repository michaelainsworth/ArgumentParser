#include <ArgumentParser/ArgumentParser.hpp>

ArgumentParser::Status ArgumentParser::getArguments(std::string& first, Arguments &args) {
    std::cout << "=> ";
    
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cout << std::endl;
        return StatusEnd;
    }
    
    std::string arg;
    
    bool topOk = true;
    for (std::string::size_type i = 0, l = line.length(); i < l; ++i) {
        char c = line[i];
        if (std::isspace(c)) {
            if (arg.size()) {
                args.push_back(arg);
                arg = "";
            }
        } else if ('"' == c) {
            bool ok = false;
            for (++i; i < l; ++i) {
                c = line[i];
                if ('"' == c) {
                    args.push_back(arg);
                    arg = "";
                    ok = true;
                    break;
                } else if ('\\' == c) {
                    if (i < l - 1 && '"' == line[i+1]) {
                        arg += line[i+1];
                        ++i;
                    }
                } else {
                    arg += c;
                }
            }
            
            if (!ok) {
                topOk = false;
                std::cerr << "Invalid double-quoted string." << std::endl;
                break;
            }
        } else if ('\'' == c) {
            bool ok = false;
            for (++i; i < l; ++i) {
                c = line[i];
                if ('\'' == c) {
                    args.push_back(arg);
                    arg = "";
                    ok = true;
                    break;
                } else if ('\\' == c) {
                    if (i < l - 1 && '\'' == line[i+1]) {
                        arg += line[i+1];
                        ++i;
                    }
                } else {
                    arg += c;
                }
            }
            
            if (!ok) {
                topOk = false;
                std::cerr << "Invalid single-quoted string." << std::endl;
                break;
            }
        } else {
            arg += c;
        }
    }
    
    if (arg.length()) {
        args.push_back(arg);
    }
    
    if (topOk) {
        if (!args.size()) {
            std::cerr << "You must enter a command." << std::endl;
            return StatusError;
        } else {
            Arguments other;
            Arguments::iterator it = args.begin(), end = args.end();
            unsigned i = 0;
            for (; it != end; ++it) {
                if (0 == i) {
                    first = *it;
                } else {
                    other.push_back(*it);
                }
                ++i;
            }
            
            args = other;
            
            return StatusOk;
        }
    } else {
        return StatusError;
    }
}
