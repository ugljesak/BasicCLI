#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include "Command.h"
#include "../utils/Reader.h"
#include "../utils/Exception.h"

class BaseCommand;

struct Args {
    std::vector<std::string> positionals;
    std::string option;

    void addPositional(const std::string& positional) {
        positionals.push_back(positional);
    }
    // void addOption(const std::string& option) {
    //     options.push_back(option);
    // }

    [[nodiscard]] bool hasOption() const {
        return !option.empty();
    }
};

class BaseCommand : public ICommand {
    friend struct Args;

protected:
    Args m_Args;

    int m_MinPositionals = 0;
    int m_MaxPositionals = 0;
    std::vector<std::string> m_AllowedOpts;

    void parseArguments(const std::vector<std::string>& rawArgs) {
        for (const auto& arg : rawArgs) {
            if (arg.empty()) continue;

            if (Reader::isOption(arg)) {
                if (m_Args.hasOption()) throw ArgumentError(this->getName(), "Given more options than allowed.");
                m_Args.option = arg;
            }
            else m_Args.addPositional(arg);
        }

        if (m_Args.positionals.size() < m_MinPositionals || m_Args.positionals.size() > m_MaxPositionals)
            throw ArgumentError(this->getName(), "Unexpected number of arguments passed.");
    }

    void execute(std::istream& in, std::ostream& out) override = 0;
    std::string manual() override = 0;

    std::string getName() {
        const std::string name = manual();
        return name.substr(0, name.find_first_of(" \t\n"));
    }
};

#endif // BASE_COMMAND_H