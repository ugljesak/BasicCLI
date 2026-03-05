#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>

#include "Registry.h"
#include "../utils/Parser.h"

class CLI {

public:
    explicit CLI(Registry& reg, std::istream& cmdIn = std::cin, std::istream& dataIn = std::cin, std::ostream& dataOut = std::cout);
    virtual ~CLI() = default;

    [[nodiscard]] bool isRunning() const { return m_IsRunning; }
    void setPrompt(const std::string& promptString);
    void run();
    void stop();

private:
    Registry& m_CommandRegistry;
    std::string m_PromptString;
    bool m_IsRunning;
    std::istream& m_CmdIn;
    std::istream& m_DataIn;
    std::ostream& m_DataOut;

    void executePipeline(const Pipeline& pipeline) const;
};


#endif  // CLI_H