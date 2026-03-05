#include "WordCount.h"
#include "../utils/Logger.h"
#include "../utils/Parser.h"
#include <fstream>

WordCount::WordCount(const std::vector<std::string> &args) {
    m_MinPositionals = 0;
    m_MaxPositionals = 1;

    parseArguments(args);
    if (!m_Args.hasOption()) throw ArgumentError(this->getName(), "Missing option, available -c and -w.");
    if (m_Args.option.size() > 2) throw ArgumentError(this->getName(), "Unknown option '" + m_Args.option + "' passed.");
}

void WordCount::execute(std::istream& in, std::ostream& out) {

    const char option = m_Args.hasOption() ? m_Args.option[1] : '\0';
    const std::string arg = m_Args.positionals.empty() ? "" : m_Args.positionals[0];

    processWithStream(arg, in, [&](std::istream& finalStream) -> void {
        const std::string str = Reader::getInput(finalStream);
        int result;
        switch (option) {
            case 'w':
                result = countWords(str);
                break;
            case 'c':
                result = countChars(str);
                break;
            default:
                throw ArgumentError(this->getName(), "Unknown option '" + m_Args.option + "' passed.");
        }
        out << result << '\n';
    });
}

std::string WordCount::manual() {
    return "wc -opt [argument]";
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