#include "Head.h"
#include "../utils/Exception.h"

Head::Head(const std::vector<std::string> &args) {
    m_MinPositionals = 0;
    m_MaxPositionals = 1;

    parseArguments(args);
    if (!m_Args.hasOption()) throw ArgumentError(this->getName(), "Missing option, available -n{count}.");
    if (m_Args.option[1] != 'n') throw ArgumentError(this->getName(), "Invalid option format '--n{count}', but given '" + m_Args.option + "'.");
    try {
        m_LineNumber = std::stoi(m_Args.option.substr(2));
    }
    catch (...) {
        throw ArgumentError(this->getName(), "Invalid option format '--n{count}', but given '" + m_Args.option + "'.");
    }
}

void Head::execute(std::istream &in, std::ostream &out) {
    std::string arg = m_Args.positionals.empty() ? "" : m_Args.positionals[0];

    processWithStream(arg, in, [&](std::istream& finalStream) {
        int count = 0;
        std::string currLine;
        std::vector<std::string> lines;
        while (std::getline(finalStream, currLine)) lines.push_back(currLine);

        for (const auto& line : lines) {
            out << line << '\n';
            ++count;
            //if (count < m_LineNumber - 1) out << '\n';
            if (count == m_LineNumber) break;
        }
    });
}

std::string Head::manual() {
    return "head -n{count} [argument]";
}
