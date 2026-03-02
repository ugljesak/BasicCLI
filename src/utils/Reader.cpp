#include "Reader.h"

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

    bool isOption(const std::string& token) {
        return (token.size() >= 2 && token[0] == '-');
    }

    void stripQuotes(std::string& str) {
        if (str.back() == '"') str.pop_back();
        if (str.front() == '"') str.erase(0, 1);
    }

    bool inQuotes(const std::string& str) {
        return str[str.size() - 1] == '"';
    }

}  // namespace Reader