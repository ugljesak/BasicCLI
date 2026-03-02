#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

#include "../interfaces/Command.h"

class Parser {
public:
    explicit Parser(const std::string& line);

    Pipeline parse() const;

private:
    std::string m_Line;

    std::vector<std::string> tokenize() const;
};

#endif  // TOKENIZER_H