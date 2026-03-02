#include "Echo.h"
#include "../utils/Logger.h"
#include "../utils/Parser.h"
#include <fstream>

void Echo::execute(const CommandData& data) {
    if (data.args.size() > 1) Logger::warning("Unexpected arguments passed.");
    std::string str;
    if (data.args.empty()) {
        str = Parser::getInput(data.input);
    }
    else if (Parser::inQuotes(data.args[0].second)) {
        str = data.args[0].second;
        Parser::stripQuotes(str);
        str += '\n';
    }
    else if (data.args[0].second.at(0) == '"') {
        str = data.args[0].second + '\n';
        str += Parser::getInput(data.input, '"');
        Parser::stripQuotes(str);
    }
    else {
        std::string filename = data.args[0].second;
        std::ifstream input(filename);
        if (!input.is_open()) throw std::runtime_error("Error opening file `" + filename + "`.");
        str = Parser::getInput(input);
        input.close();
    }
    data.output << str;
}
