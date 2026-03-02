#ifndef I_COMMAND_H
#define I_COMMAND_H

#include <vector>
#include <string>
#include <iostream>

typedef std::string Arg;

struct CommandData {
    std::string name;
    std::vector<std::string> args;
    std::string inputFile = "";
    std::string outputFile = "";
    bool append = false;
};

struct Pipeline {
    std::vector<CommandData> commands;

    void append(const CommandData& data) { commands.push_back(data); }
    bool isEmpty() const { return commands.empty(); }
};

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual void execute(const CommandData& data) = 0;
};

class BaseCommand : public ICommand {
protected:
    ParsedArgs m_Args;

    // Конфигурација коју подешава дете класа
    int m_MinPositionals = 0;
    int m_MaxPositionals = 0;
    std::vector<std::string> m_AllowedFlags; // нпр "-w", "-c"
    std::string m_PrefixOption = "";         // нпр "-n" за head

    void parseAndValidate(const std::vector<std::string>& rawArgs) {
        for (const auto& arg : rawArgs) {
            // Да ли је опција са префиксом (нпр. head -n5)
            if (!m_PrefixOption.empty() && arg.find(m_PrefixOption) == 0) {
                m_Args.options[m_PrefixOption] = arg.substr(m_PrefixOption.length());
            }
            // Да ли је обичан флег (нпр. wc -w)
            else if (arg[0] == '-') {
                // Провера да ли је флег дозвољен може ићи овде
                m_Args.options[arg] = "";
            }
            // Иначе је позициони аргумент
            else {
                m_Args.positionals.push_back(arg);
            }
        }

        // Аутоматска валидација броја позиционих аргумената
        if (m_Args.positionals.size() < m_MinPositionals || m_Args.positionals.size() > m_MaxPositionals) {
            throw std::runtime_error("Грешка: Неисправан број аргумената.");
        }
    }
};


#endif  // I_COMMAND_H