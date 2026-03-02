#ifndef BINARYCOMMAND_H
#define BINARYCOMMAND_H

#include "Command.h"

template<typename T1, typename T2>
class BinaryCommand : ICommand {
public:
    explicit BinaryCommand(BinaryCommand& command) = default;
    explicit BinaryCommand(std::vector<std::string> args, std::istream& input = std::cin, std::ostream& output = std::cout)
    : ICommand(input, output), {}

    void execute() override = 0;
protected:
    T1 m_Arg1;
    T2 m_Arg2;
};

#endif // BINARYCOMMAND_H