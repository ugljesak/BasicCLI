#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "../interfaces/StreamCommand.h"

class Translate : public StreamCommand {
public:
    explicit Translate(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;

private:
    std::string m_Text;
    std::string m_What, m_With;
};


#endif  // TRANSLATE_H