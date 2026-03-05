//
// Created by ugoboss on 3/4/26.
//

#ifndef PROJEKATCLAV_TRUNCATE_H
#define PROJEKATCLAV_TRUNCATE_H

#include "../interfaces/BaseCommand.h"

class Truncate : public BaseCommand {
public:
    explicit Truncate(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;

};


#endif //PROJEKATCLAV_TRUNCATE_H