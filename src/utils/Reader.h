#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>

namespace Reader {
    void stripQuotes(std::string& str);
    bool inQuotes(const std::string& str);
    std::string getInput(std::istream& input, char terminator = '\0');
    bool isOption(const std::string& token);

}  // namespace Reader


#endif  // READER_H