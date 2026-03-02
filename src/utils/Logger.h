#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

class Logger {
public:
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
private:
    // Copying and creating logger class is forbidden.
    Logger();

    void logMessage(const std::string& type, const std::string& message) const;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    std::ostream& m_OutputStream;
};

#endif