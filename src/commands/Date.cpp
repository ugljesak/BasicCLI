#include "Date.h"
#include "../utils/Logger.h"
#include <ctime>

void Date::execute(const CommandData& data) {
    if (!data.args.empty()) Logger::warning("Prosledjeni neocekivani argumenti.");

    const time_t now = time(0);
    const struct tm ts = *localtime(&now);
    char localTime[20];
    strftime(localTime, sizeof(localTime), "%d.%m.%Y", &ts);

    data.output << localTime << std::endl;
}
