#include "Remove.h"
#include "../utils/Logger.h"
#include <fstream>
#include <cstdio>
#include <filesystem>

void Remove::execute(const CommandData& data) {
    if (data.args.size() != 1 || (data.args.size() == 1 && !data.args[0].first.empty())) {
        Logger::error("Missing file operand.");
        return;
    }

    const std::string& filename = data.args[0].second;
    std::ifstream file(filename);
    if (!file.good()) {
        throw std::runtime_error("File not found.");
    }
    std::remove(filename.c_str());
    Logger::info("File `" + filename + "` successfully deleted.");
}
