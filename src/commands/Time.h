#ifndef TIME_H
#define TIME_H

#include "../interfaces/Command.h"

class Time : public ICommand {
public:
    void execute(const CommandData& data) override;
};


#endif  // TIME_H