#include <iostream>

#include "commands/Batch.h"
#include "commands/Echo.h"
#include "commands/Date.h"
#include "commands/Head.h"
#include "commands/Prompt.h"
#include "commands/Remove.h"
#include "commands/Time.h"
#include "commands/Touch.h"
#include "commands/Translate.h"
#include "commands/WordCount.h"
#include "commands/Truncate.h"
#include "core/CLI.h"

// Entry point of our application
int main() {
    Registry reg;
    CLI cli(reg);

    reg.registerCommand("echo", [](const std::vector<std::string>& args) {return std::make_unique<Echo>(args);});
    reg.registerCommand("date", [](const std::vector<std::string>& args) {return std::make_unique<Date>(args);});
    reg.registerCommand("time", [](const std::vector<std::string>& args) {return std::make_unique<Time>(args);});
    reg.registerCommand("wc", [](const std::vector<std::string>& args) {return std::make_unique<WordCount>(args);});
    reg.registerCommand("touch", [](const std::vector<std::string>& args) {return std::make_unique<Touch>(args);});
    reg.registerCommand("rm", [](const std::vector<std::string>& args) {return std::make_unique<Remove>(args);});
    reg.registerCommand("truncate", [](const std::vector<std::string>& args) {return std::make_unique<Truncate>(args);});
    reg.registerCommand("rm", [](const std::vector<std::string>& args) {return std::make_unique<Remove>(args);});
    reg.registerCommand("prompt", [&cli](const std::vector<std::string>& args) {return std::make_unique<Prompt>(args, cli);});
    reg.registerCommand("tr", [](const std::vector<std::string>& args) {return std::make_unique<Translate>(args);});
    reg.registerCommand("head", [](const std::vector<std::string>& args) {return std::make_unique<Head>(args);});
    reg.registerCommand("batch", [&reg](const std::vector<std::string>& args) {return std::make_unique<Batch>(args, reg);});

    cli.run();

    return 0;
}