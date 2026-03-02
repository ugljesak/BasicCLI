#include "WordCount.h"
#include "../utils/Logger.h"
#include "../utils/Parser.h"
#include <fstream>

void WordCount::execute(const CommandData& data) {
    if (data.args.empty()) {
        throw std::runtime_error("Missing command argument.");
    }

    const std::string& option = data.args[0].first;

    std::string str;
    if (data.args[0].second.empty()) {
        str = Parser::getInput(data.input);
    }
    else if (Parser::inQuotes(data.args[0].second)) {
        str = data.args[0].second;
        Parser::stripQuotes(str);
    }
    else {
        std::string filename = data.args[0].second;
        std::ifstream input(filename);
        if (!input.is_open()) throw std::runtime_error("Error opening file `" + filename + "`.");
        str = Parser::getInput(input);
        input.close();
    }
    int result;
    if (option == "-w") result = countWords(str);
    else if (option == "-c") result = countChars(str);
    else throw std::runtime_error("Unknown option, supported -w and -c.");
    data.output << result << std::endl;
}

int WordCount::countChars(const std::string& str) {
    return static_cast<int>(str.size());
}

int WordCount::countWords(const std::string& str) {
    int wordCount = 0;
    bool isWord = false;
    for (const char& ch : str) {
        if (std::isspace(ch)) {
            if (isWord == false) continue;
            ++wordCount;
            isWord = false;
        }
        else isWord = true;
    }
    if (isWord) ++wordCount;
    return wordCount;
}