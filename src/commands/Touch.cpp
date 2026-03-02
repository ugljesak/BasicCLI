#include "Touch.h"

#include <filesystem>

#include "../utils/Logger.h"
#include <fstream>


void Touch::execute(const CommandData &data) {
    if (data.args.size() != 1 || (data.args.size() == 1 && !data.args[0].first.empty())) {
        throw std::runtime_error("Missing file operand.");
        return;
    }
    const std::string& filename = data.args[0].second;
    if (std::filesystem::exists(filename)) {
        throw std::runtime_error("File `" + filename + "` already exists.");
    }
    std::ofstream file(filename, std::ios::app);
    file.close();


}