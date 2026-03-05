//
// Created by ugoboss on 3/4/26.
//

#ifndef HEAD_H
#define HEAD_H

#include "../interfaces/StreamCommand.h"

class Head : public StreamCommand {
public:
    explicit Head(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;

private:
    int m_LineNumber;
};


#endif  // HEAD_H