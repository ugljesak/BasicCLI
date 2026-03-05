#include "Echo.h"
#include "../utils/Logger.h"
#include "../utils/Parser.h"

Echo::Echo(const std::vector<std::string>& args) {
    m_MinPositionals = 0;
    m_MaxPositionals = 1;

    parseArguments(args);
}

void Echo::execute(std::istream& in, std::ostream& out) {

    const std::string arg = m_Args.positionals.empty() ? "" : m_Args.positionals[0];

    processWithStream(arg, in, [&](std::istream& finalStream) -> void {
        out << Reader::getInput(finalStream);
    });
}

std::string Echo::manual() {
    return "echo [argument]";
}