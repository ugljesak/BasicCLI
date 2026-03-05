#include "Translate.h"
#include "../utils/Reader.h"

Translate::Translate(const std::vector<std::string> &args) {
    m_MinPositionals = 0;
    m_MaxPositionals = 2;

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];

        if (Reader::isOption(arg)) {
            m_What = Reader::stripQuotes(arg.substr(1));
            if (i < args.size() - 1) {
                m_With = Reader::stripQuotes(args[i + 1]);
                ++i;
            }
        }
        else {
            if (m_What.empty()) m_Text = arg;
            else throw ArgumentError(this->getName(), "Unexpected argument '" + arg + "' after [with] parameter.");
        }
    }

    if (m_What.empty()) throw ArgumentError(this->getName(), "Option -what is mandatory, but not provided.");
}

void Translate::execute(std::istream &in, std::ostream &out) {

    processWithStream(m_Text, in, [&](std::istream& finalStream) -> void {
        std::string line;

        while (std::getline(finalStream, line)) {
            size_t pos = 0;
            while ((pos = line.find(m_What, pos)) != std::string::npos) {
                line.replace(pos, m_What.length(), m_With);
                pos += m_With.size();
            }

            out << line << '\n';
        }
    });
}

std::string Translate::manual() {
    return "tr [argument] -what [with]";
}
