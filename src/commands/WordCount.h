#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include "../interfaces/Command.h"

class WordCount : public ICommand {
public:
    void execute(const CommandData& data) override;
private:
    static int countWords(const std::string& str);
    static int countChars(const std::string& str);
};


#endif  // WORDCOUNT_H