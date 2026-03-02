#include "Registry.h"
#include "../utils/Logger.h"


Registry::Registry() {}

Registry::~Registry() {
    for(auto it=m_Commands.begin(); it!=m_Commands.end(); ++it){
        delete it->second;
    }
    m_Commands.clear();
}

void Registry::registerCommand(const std::string& name, ICommand* command) {
    
    if(m_Commands.find(name) != m_Commands.end()){
        delete m_Commands[name];
        Logger::warning("Command with alias `" + name + "` already registered.");
    }
    m_Commands[name] = command;
}

ICommand* Registry::getCommand(const std::string& name) {
        
    if(m_Commands.find(name) == m_Commands.end()) {
        Logger::error("Command `" + name + "` not found in registry.");
        return nullptr;
    }
    return m_Commands[name];
}