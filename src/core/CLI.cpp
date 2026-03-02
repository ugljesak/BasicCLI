#include "CLI.h"
#include "../utils/Logger.h"
#include <sstream>
#include <fstream>

#include "../utils/Exception.h"


CLI::CLI(Registry& reg)
    : m_CommandRegistry(reg), m_PromptString("$"), m_IsRunning(true) {}
        
void CLI::setPrompt(const std::string& promptString) {
    m_PromptString = promptString;
}

void CLI::stop() {
    m_IsRunning = false;
}

void CLI::run() {
    std::string line;
    Logger::info("CLI started.");

    while (m_IsRunning) {
        std::cout << m_PromptString << " ";

        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) {
                std::cout << std::endl;
                break;
            }
            std::cin.clear();
            continue;
        }
        if (line.empty()) continue;

        try {
            Pipeline p = parser->parse(line);
            executePipeline(p);

            if (std::cin.eof()) {
                std::cin.clear();
                // clearerr(stdin);
            }
        }
        catch (const ShellException& e) {
            Logger::error(e.what());
        }
        catch (const std::exception& e) {
            Logger::error(e.what());
        }
    }
    
    Logger::info("CLI stopped.");
}

void CLI::executePipeline(const Pipeline& pipeline) {
    if (pipeline.commands.empty()) return;

    std::stringstream currStream;

    for (size_t i = 0; i < pipeline.commands.size(); ++i) {
        const CommandData& cmd = pipeline.commands[i];

        std::istream* currInput = &std::cin;
        std::ostream* currOutput = &std::cout;

        std::ifstream inFile;
        std::ofstream outFile;
        std::stringstream nextStream;

        if (!cmd.inputFile.empty()) {
            inFile.open(cmd.inputFile);
            if (!inFile.is_open()) throw ExecutionError("Cannot open file:  " + cmd.inputFile);
            currentInput = &inFile;
        }
        else if (i > 0) {
            currentInput = &currStream;
        }

        if (!cmd.outputFile.empty()) {
            std::ios::openmode mode = cmd.append ? std::ios::app : std::ios::out;
            outFile.open(cmd.outputFile, mode);
            if (!outFile.is_open()) throw ExecutionError("Не могу да отворим фајл за упис: " + cmd.outputFile);
            currentOutput = &outFile;
        }
        else if (i < pipeline.commands.size() - 1) {
            currentOutput = &nextStream;
        }

        ICommand* command = m_CommandRegistry.getCommand(cmd.name)(inp);
        if (command == nullptr) throw CommandNotFoundError(cmd.name);


        if (i < pipeline.commands.size() - 1) {
            currStream.str(nextStream.str());
            currStream.clear();
        }
    }
}