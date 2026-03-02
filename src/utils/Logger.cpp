#include "Logger.h"


Logger::Logger() : m_OutputStream(std::cout) {}

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
    m_OutputStream << "[" << type << "] " << message << std::endl;
}