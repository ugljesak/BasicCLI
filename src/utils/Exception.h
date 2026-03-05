#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

// Base class for exceptions. b
class ShellException : public std::runtime_error {
public:
    ShellException(const std::string& msg) : std::runtime_error(msg) {}
};

// For lexical errors, illegal characters etc.
class LexicalError : public ShellException {
public:
    LexicalError(const std::string& originalLine, const std::string& markerLine)
        : ShellException("Lexical Error: Unexpected characters:\n" + originalLine + "\n" + markerLine) {}
};

// Semantic errors for pipelines and redirections.
class SemanticError : public ShellException {
public:
    SemanticError(const std::string& msg) : ShellException("Semantic Error: " + msg) {}
};

// Parser errors, quotes, pipes, redirections etc.
class SyntaxError : public ShellException {
public:
    SyntaxError(const std::string& msg) : ShellException("Syntax Error: " + msg) {}
};

// runtime errors, file not found, bad permissions etc.
class ExecutionError : public ShellException {
public:
    ExecutionError(const std::string& msg) : ShellException("Execution Error: " + msg) {}
};

class FileIOError : public ExecutionError {
public:
    FileIOError(const std::string& filename) : ExecutionError("Cannot open file '" + filename + "'.") {}
};

// Bad type of argument, bad number of arguments etc.
class ArgumentError : public ShellException {
public:
    ArgumentError(const std::string& cmdName, const std::string& msg) 
        : ShellException(cmdName + ": " + msg) {}
};

// Register error for unknown command.
class CommandNotFoundError : public ShellException {
public:
    CommandNotFoundError(const std::string& cmdName) 
        : ShellException("Unknown command: " + cmdName) {}
};

#endif  // EXCEPTION_H