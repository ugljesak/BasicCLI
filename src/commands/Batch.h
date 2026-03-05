#ifndef BATCH_H
#define BATCH_H

#include "../core/Registry.h"
#include "../interfaces/BaseCommand.h"

class Batch : public BaseCommand {
public:
    explicit Batch(const std::vector<std::string>& args, Registry& reg);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;

private:
    Registry& m_Registry;
};


#endif  // BATCH_H