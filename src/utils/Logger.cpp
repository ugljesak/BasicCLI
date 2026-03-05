#include "Logger.h"

const std::string LOG_FILE = "DebugCLI.log";

void Logger::info(const std::string& message) {
    getInstance().logMessage("INFO", message);
}
void Logger::warning(const std::string& message) {
    getInstance().logMessage("WARN", message);
}
void Logger::error(const std::string& message) {
    getInstance().logMessage("ERROR", message);
}

void Logger::logMessage(const std::string& type, const std::string& message) const {
    std::ofstream file(LOG_FILE, std::ios::app);
    if (file.is_open()) file << "[" << type << "] " << message << std::endl;
    file.close();
}