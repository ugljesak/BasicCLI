#include <iostream>
#include "commands/Echo.h"
#include "commands/Date.h"
#include "commands/Remove.h"
#include "commands/Time.h"
#include "commands/Touch.h"
#include "commands/WordCount.h"
#include "core/CLI.h"

// Entry point of our application
int main() {

    Registry registry;
    registry.registerCommand("echo", new Echo());
    registry.registerCommand("time", new Time());
    registry.registerCommand("date", new Date());
    registry.registerCommand("touch", new Touch());
    registry.registerCommand("wc", new WordCount());
    //registry.registerCommand("rm", new Remove());

    CLI cli(registry);
    cli.run();

    return 0;
}