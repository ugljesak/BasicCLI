#ifndef TOUCH_H
#define TOUCH_H

#include "../interfaces/Command.h"

class Touch : public ICommand {
public:
    void execute(const CommandData &data) override;
};

#endif  // TOUCH_H