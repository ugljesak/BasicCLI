//
// Created by ugoboss on 3/4/26.
//

#include "Prompt.h"

Prompt::Prompt(const std::vector<std::string> &args, CLI &cli) : m_CLI(cli) {
    m_MinPositionals = 1;
    m_MaxPositionals = 1;

    parseArguments(args);
}

void Prompt::execute(std::istream &in, std::ostream &out) {
    m_CLI.setPrompt(Reader::stripQuotes(m_Args.positionals[0]));
}

std::string Prompt::manual() {
    return "prompt argument";
}
