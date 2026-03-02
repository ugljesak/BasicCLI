#ifndef REGISTRY_H
#define REGISTRY_H

#include <map>
#include <memory>
#include "../interfaces/Command.h"


class Registry {

public:
    Registry();
    ~Registry();

    void registerCommand(const std::string& name, ICommand* command);

    ICommand* getCommand(const std::string& name);

private:
    std::map<std::string, ICommand*> m_Commands;

};


#endif  // REGISTRY_H