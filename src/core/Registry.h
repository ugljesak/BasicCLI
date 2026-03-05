#ifndef REGISTRY_H
#define REGISTRY_H

#include <functional>
#include <map>
#include <memory>
#include "../interfaces/Command.h"


class Registry {
    using CreateFunc = std::function<std::unique_ptr<ICommand>(const std::vector<std::string>&)>;

public:
    Registry() = default;
    ~Registry();

    void registerCommand(const std::string& name, CreateFunc func);

    std::unique_ptr<ICommand> createCommand(const std::string& name, const std::vector<std::string>& args);

private:
    std::map<std::string, CreateFunc> m_Commands;

};


#endif  // REGISTRY_H