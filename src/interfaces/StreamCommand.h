#ifndef STREAM_COMMAND_H
#define STREAM_COMMAND_H

#include <functional>
#include <sstream>
#include <fstream>
#include "BaseCommand.h"
#include "../utils/Reader.h"

class StreamCommand : public BaseCommand {

protected:
    static void processWithStream(const std::string& arg, std::istream& in, std::function<void(std::istream&)> slaveFunc) {

        if (!arg.empty() && &in != &std::cin) {
            throw SemanticError("Command cannot have input stream itself while in pipeline '|' or having input redirection '<'.");
        }
        if (arg.empty()) {
            slaveFunc(in);
        }
        else if (Reader::inQuotes(arg)) {
            std::stringstream ss(Reader::stripQuotes(arg));
            slaveFunc(ss);
        }
        else {
            std::ifstream file(arg);
            if (!file.is_open()) throw FileIOError(arg);
            slaveFunc(file);
            file.close();
        }
    }

    void execute(std::istream& in, std::ostream& out) override = 0;
    std::string manual() override = 0;
};


#endif  // STREAM_COMMAND_H