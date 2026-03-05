//
// Created by ugoboss on 3/4/26.
//

#ifndef PROMPT_H
#define PROMPT_H

#include "../interfaces/BaseCommand.h"
#include "../core/CLI.h"

class Prompt : public BaseCommand {
public:
    explicit Prompt(const std::vector<std::string>& args, CLI& cli);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;

private:
    CLI& m_CLI;
};


#endif  // PROMPT_H