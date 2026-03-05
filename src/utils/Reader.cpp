#include "Reader.h"
#include "Exception.h"

namespace Reader {
    std::string getInput(std::istream& input, const char terminator) {
        std::string str;
        char ch;
        if (terminator == '\0') {
            while (input.get(ch)) str += ch;
        }
        else {
            while (true) {
                input.get(ch);
                if (ch == terminator) break;
                str += ch;
            }
        }
        return str;
    }

    std::string getLine(std::istream& input) {
        std::string line;
        if (!std::getline(input, line)) return "";
        return line;
    }

    bool isOption(const std::string& token) {
        return (token.size() >= 2 && token[0] == '-');
    }

    std::string stripQuotes(const std::string& str) {
        if (!inQuotes(str)) throw ArgumentError("tr", "Parameter not in quotes.");
        return str.substr(1, str.size() - 2);
    }

    bool inQuotes(const std::string& str) {
        return str[str.size() - 1] == '"';
    }

}  // namespace Reader