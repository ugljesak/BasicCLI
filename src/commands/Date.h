#ifndef DATE_H
#define DATE_H

#include "../interfaces/Command.h"

class Date : public ICommand {
public:
    void execute(const CommandData& data) override;
};


#endif  // DATE_H