#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>

#include "Registry.h"
#include "../utils/Parser.h"

class CLI {

public:
    CLI(Registry& reg);
    virtual ~CLI() = default;

    CLI& getInstance() { return *this; }

    bool isRunning() const { return m_IsRunning; }
    void setPrompt(const std::string& promptString);
    void run();
    void stop();

private:
    Registry& m_CommandRegistry;
    std::string m_PromptString;
    bool m_IsRunning;

    void executePipeline(const Pipeline& pipeline);
};


#endif  // CLI_H