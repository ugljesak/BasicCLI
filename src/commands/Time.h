#ifndef TIME_H
#define TIME_H

#include "../interfaces/BaseCommand.h"

class Time : public BaseCommand {
public:
    explicit Time(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;
};


#endif  // TIME_H