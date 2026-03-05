#ifndef DATE_H
#define DATE_H

#include "../interfaces/BaseCommand.h"

class Date : public BaseCommand {
public:
    explicit Date(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;
};


#endif  // DATE_H