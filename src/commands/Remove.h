#ifndef REMOVE_H
#define REMOVE_H

#include "../interfaces/Command.h"

class Remove : public ICommand {
public:
    void execute(const CommandData &data) override;
};

#endif  // REMOVE_H