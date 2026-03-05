#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>

namespace Reader {
    std::string stripQuotes(const std::string& str);
    bool inQuotes(const std::string& str);

    std::string getLine(std::istream& input = std::cin);
    std::string getInput(std::istream& input, char terminator = '\0');

    bool isOption(const std::string& token);

}  // namespace Reader


#endif  // READER_H