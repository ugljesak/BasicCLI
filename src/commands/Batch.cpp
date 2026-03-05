#include "Batch.h"
#include "../core/CLI.h"
#include <fstream>

Batch::Batch(const std::vector<std::string> &args, Registry &reg)
    : m_Registry(reg) {

    m_MinPositionals = 1;
    m_MaxPositionals = 1;

    parseArguments(args);
}

void Batch::execute(std::istream &in, std::ostream &out) {
    std::string& filename = m_Args.positionals[0];

    std::ifstream inFile(filename);
    if (!inFile.is_open()) throw FileIOError(filename);

    CLI tempCLI(m_Registry, inFile, std::cin, out);
    tempCLI.run();
}

std::string Batch::manual() {
    return "batch filename";
}
