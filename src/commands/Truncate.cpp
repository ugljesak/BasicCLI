#include "Truncate.h"
#include "../utils/Logger.h"
#include <fstream>

Truncate::Truncate(const std::vector<std::string> &args) {
    m_MinPositionals = 1;
    m_MaxPositionals = 1;

    parseArguments(args);
}

void Truncate::execute(std::istream &in, std::ostream &out) {

    const std::string& filename = m_Args.positionals[0];
    std::ofstream file(filename, std::ios::trunc);

    if (!file.is_open()) throw ExecutionError("File '" + filename + "' does not exist.");
    Logger::info("File `" + filename + "` successfully truncated.");
}

std::string Truncate::manual() {
    return "truncate filename";
}
