#include "Touch.h"
#include "../utils/Logger.h"
#include "../utils/Exception.h"

#include <filesystem>
#include <fstream>

Touch::Touch(const std::vector<std::string> &args) {
    m_MinPositionals = 1;
    m_MaxPositionals = 1;

    parseArguments(args);
}

void Touch::execute(std::istream &in, std::ostream &out) {

    const std::string& filename = m_Args.positionals[0];
    if (std::filesystem::exists(filename)) throw ExecutionError("File `" + filename + "` already exists.");

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) throw FileIOError(filename);
    file.close();
    Logger::info("File successfully created.");
}

std::string Touch::manual() {
    return "touch filename";
}
