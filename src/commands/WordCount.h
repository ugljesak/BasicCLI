#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include "../interfaces/StreamCommand.h"

class WordCount : public StreamCommand {
public:
    explicit WordCount(const std::vector<std::string>& args);

    void execute(std::istream& in, std::ostream& out) final;
    std::string manual() final;

private:
    static int countWords(const std::string& str);
    static int countChars(const std::string& str);
};


#endif  // WORDCOUNT_H