#include "Remove.h"
#include "../utils/Logger.h"
#include "../utils/Exception.h"

#include <fstream>
#include <cstdio>
#include <filesystem>

Remove::Remove(const std::vector<std::string> &args) {
    m_MinPositionals = 1;
    m_MaxPositionals = 1;

    parseArguments(args);
}

void Remove::execute(std::istream &in, std::ostream &out) {

    const std::string& filename = m_Args.positionals[0];
    std::ifstream file(filename);
    if (!file.good()) throw ExecutionError("File '" + filename + "' does not exist.");

    std::remove(filename.c_str());
    Logger::info("File `" + filename + "` successfully removed.");
}

std::string Remove::manual() {
    return "rm filename";
}
