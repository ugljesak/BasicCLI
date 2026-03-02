#ifndef ECHO_H
#define ECHO_H

#include "../interfaces/Command.h"


class Echo : public ICommand {
public:
    void execute(const CommandData& data) override;
};


#endif  // ECHO_H