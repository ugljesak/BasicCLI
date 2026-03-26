#ifndef I_COMMAND_H
#define I_COMMAND_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

struct CommandData {
    std::string name;
    std::vector<std::string> args;
    std::string inputFile;
    std::string outputFile;
    bool append = false;
};

struct Pipeline {
    std::vector<CommandData> commands;

    void append(const CommandData& data) { commands.push_back(data); }
    [[nodiscard]] bool isEmpty() const { return commands.empty(); }
};

class ICommand {
public:
    ICommand() = default;
    virtual ~ICommand() = default;

    virtual void execute(std::istream& in, std::ostream& out) = 0;
    virtual std::string manual() = 0;
};


#endif  // I_COMMAND_H