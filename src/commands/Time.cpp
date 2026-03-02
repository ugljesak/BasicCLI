#include "Time.h"
#include "../utils/Logger.h"
#include <time.h>

void Time::execute(const CommandData& data) {
    if (!data.args.empty()) Logger::warning("Prosledjeni neocekivani argumenti.");
    const time_t now = time(0);
    const struct tm ts = *localtime(&now);
    char localTime[20];
    strftime(localTime, sizeof(localTime), "%X", &ts);

    data.output << localTime << std::endl;
}
