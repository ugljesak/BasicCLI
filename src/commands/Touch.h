#ifndef TOUCH_H
#define TOUCH_H

#include "../interfaces/BaseCommand.h"

class Touch : public BaseCommand {
public:
    explicit Touch(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;
};

#endif  // TOUCH_H