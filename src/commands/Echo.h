#ifndef ECHO_H
#define ECHO_H

#include "../interfaces/StreamCommand.h"

class Echo : public StreamCommand {
public:
    explicit Echo(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;
};


#endif  // ECHO_H