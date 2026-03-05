#include "Date.h"
#include <ctime>


Date::Date(const std::vector<std::string> &args) {
    m_MinPositionals = 0;
    m_MaxPositionals = 0;

    parseArguments(args);
}

void Date::execute(std::istream &in, std::ostream &out) {

    const time_t now = time(0);
    const struct tm ts = *localtime(&now);
    char localTime[20];
    strftime(localTime, sizeof(localTime), "%d.%m.%Y", &ts);

    out << localTime << '\n';
}

std::string Date::manual() {
    return "date";
}
