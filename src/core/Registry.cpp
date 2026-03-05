#include "Registry.h"

#include <utility>
#include "../utils/Logger.h"
#include "../interfaces/Command.h"


Registry::~Registry() {
    m_Commands.clear();
}

void Registry::registerCommand(const std::string& name, CreateFunc func) {
    m_Commands[name] = std::move(func);
}

std::unique_ptr<ICommand> Registry::createCommand(const std::string& name, const std::vector<std::string>& args) {
        
    if (m_Commands.contains(name)) {
        return m_Commands[name](args);
    }
    return nullptr;
}