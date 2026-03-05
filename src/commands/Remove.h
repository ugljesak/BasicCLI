#ifndef REMOVE_H
#define REMOVE_H

#include "../interfaces/BaseCommand.h"


class Remove : public BaseCommand {
public:
    explicit Remove(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;
};

#endif  // REMOVE_H