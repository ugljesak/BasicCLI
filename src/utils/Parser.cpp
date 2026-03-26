#include "Parser.h"
#include "Logger.h"
#include "Reader.h"
#include "Exception.h"

Parser::Parser(const std::string &line)
    : m_Line(line) {}

std::vector<std::string> Parser::tokenize() const {
    std::vector<std::string> tokens;
    std::string currToken;
    bool inQ = false;

    std::string markers(m_Line.length() + 3, '~');
    bool hasError = false;

    for (size_t i = 0; i < m_Line.size(); ++i) {

        char ch = m_Line[i];
        if (ch == '"') {
            inQ = !inQ;
            currToken += ch;
            continue;
        }
        if (inQ) {
            currToken += ch;
            continue;
        }

        if (!std::isalnum(ch) && !std::isspace(ch) && ch != '-' && ch != '_' && ch != '.' && ch != '/' && ch != '|' && ch != '<' && ch != '>') {
            markers[i] = '^';
            hasError = true;
            continue;
        }

        if (ch == '|' || ch == '<' || ch == '>') {
            if (!currToken.empty()) {
                tokens.push_back(currToken);
                currToken.clear();
            }
            if (ch == '>' && i + 1 < m_Line.size() && m_Line[i+1] == '>') {
                tokens.push_back(">>");
                ++i;
            }
            else tokens.push_back(std::string(1, ch));
            continue;
        }

        if (std::isspace(ch)) {
            if (!currToken.empty()) {
                tokens.push_back(currToken);
                currToken.clear();
            }
        } else {
            currToken += ch;
        }
    }
    if (inQ) {
        markers[m_Line.std::string::rfind('"')] = '^';
        throw SyntaxError("Quotes aren't closed.");
    }
    if (hasError) throw LexicalError(m_Line, markers);

    if (!currToken.empty()) tokens.push_back(currToken);

    return tokens;
}

Pipeline Parser::parse() const {

    std::vector<CommandData> commands;
    std::vector<std::string> tokens = tokenize();

    Pipeline pipeline;
    CommandData currCmd;

    currCmd.name = tokens[0];

    for (size_t i=1; i<tokens.size(); ++i) {
        const std::string& t = tokens[i];

        if (t == "|") {
            if (currCmd.name.empty()) throw SyntaxError("Given empty command in pipeline.");
            pipeline.append(currCmd);
            currCmd = CommandData();
        }
        else if (t == "<") {
            if (i >= tokens.size() - 1) throw SyntaxError(currCmd.name + ": Missing filename for input redirection '<'.");
            if (!currCmd.inputFile.empty()) throw SemanticError(currCmd.name + ": More than 1 input redirections '<' forbidden.");
            currCmd.inputFile = tokens[++i];
        }
        else if (t == ">") {
            if (i >= tokens.size() - 1) throw SyntaxError(currCmd.name + ": Missing filename for output redirection '>'.");
            if (!currCmd.outputFile.empty()) throw SemanticError(currCmd.name + ": More than 1 output redirections '>' forbidden.");
            currCmd.outputFile = tokens[++i];
            currCmd.append = false;
        }
        else if (t == ">>") {
            if (i + 1 >= tokens.size()) throw SyntaxError(currCmd.name + ": Missing filename for output redirection '>>'.");
            if (!currCmd.outputFile.empty()) throw SemanticError(currCmd.name + ": More than 1 output redirections '>>' forbidden.");
            currCmd.outputFile = tokens[++i];
            currCmd.append = true;
        }
        else {
            if (currCmd.name.empty()) currCmd.name = t;
            else currCmd.args.push_back(t);
        }
    }
    if (!currCmd.name.empty()) pipeline.append(currCmd);
    else if (!tokens.empty() && tokens.back() == "|") throw SyntaxError("Line is ending with |.");

    for (size_t i = 0; i < pipeline.commands.size(); ++i) {
        const auto& cmd = pipeline.commands[i];

        if (i > 0 && !cmd.inputFile.empty()) {
            throw SemanticError("Command '" + cmd.name + "' has input from pipe, cannot have input redirection.");
        }
        if (i < pipeline.commands.size() - 1 && !cmd.outputFile.empty()) {
            throw SemanticError("Command '" + cmd.name + "' has output to pipe, cannot have output redirection.");
        }
    }

    return pipeline;
}
