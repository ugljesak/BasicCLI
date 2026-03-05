#include "CLI.h"
#include "../utils/Logger.h"
#include <sstream>
#include <fstream>

#include "../utils/Exception.h"
#include "../commands/Echo.h"

CLI::CLI(Registry& reg, std::istream& cmdIn, std::istream& dataIn, std::ostream& dataOut)
    : m_CommandRegistry(reg), m_PromptString("$"), m_IsRunning(false),
        m_CmdIn(cmdIn), m_DataIn(dataIn), m_DataOut(dataOut) {}
        
void CLI::setPrompt(const std::string& promptString) {
    m_PromptString = promptString;
}

void CLI::stop() {
    m_IsRunning = false;
}

void CLI::run() {
    m_IsRunning = true;
    if (&m_CmdIn == &std::cin) Logger::info("CLI started.");

    std::string line;
    while (m_IsRunning) {
        if (&m_CmdIn == &std::cin) std::cout << m_PromptString << ' ';

        if (!std::getline(m_CmdIn, line)) {
            if (line.size() > 512) line = line.substr(0, 512);
            if (m_CmdIn.eof()) {
                if (&m_CmdIn == &std::cin) m_DataOut << std::endl;
                this->stop();
                break;
            }
            m_CmdIn.clear();
            continue;
        }
        if (line.empty()) continue;

        try {
            Parser parser(line);
            Pipeline p = parser.parse();
            executePipeline(p);

            if (std::cin.eof()) {
                std::cin.clear();
                clearerr(stdin);
            }
        }
        catch (const ShellException& e) {
            m_DataOut << e.what() << '\n';
            Logger::error(e.what());
        }
        catch (const std::exception& e) {
            Logger::error(e.what());
        }
    }
    
    if (&m_CmdIn == &std::cin) Logger::info("CLI stopped.");
}

void CLI::executePipeline(const Pipeline& pipeline) const {
    if (pipeline.commands.empty()) return;

    std::stringstream currStream;

    for (size_t i = 0; i < pipeline.commands.size(); ++i) {
        const CommandData& cmd = pipeline.commands[i];

        std::istream* currInput = &m_DataIn;
        std::ostream* currOutput = &m_DataOut;

        std::ifstream inFile;
        std::ofstream outFile;
        std::stringstream nextStream;

        if (!cmd.inputFile.empty()) {
            inFile.open(cmd.inputFile);
            if (!inFile.is_open()) throw FileIOError(cmd.inputFile);
            currInput = &inFile;
        }
        else if (i > 0) {
            currInput = &currStream;
        }

        if (!cmd.outputFile.empty()) {
            std::ios::openmode mode = cmd.append ? std::ios::app : std::ios::out;
            outFile.open(cmd.outputFile, mode);
            if (!outFile.is_open()) throw FileIOError(cmd.outputFile);
            currOutput = &outFile;
        }
        else if (i < pipeline.commands.size() - 1) {
            currOutput = &nextStream;
        }

        std::unique_ptr<ICommand> command = m_CommandRegistry.createCommand(cmd.name, cmd.args);
        if (command == nullptr) throw CommandNotFoundError(cmd.name);
        command->execute(*currInput, *currOutput);

        if (i < pipeline.commands.size() - 1) {
            currStream.str(nextStream.str());
            currStream.clear();
        }
    }
}
