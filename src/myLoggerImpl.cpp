#include "Arduino.h"
#include "ESP32LoggingHelper.h"

void getDebugLevels()
{
int loggersCount = loggerList::getLoggersCount();
    
    log_d("Loggers disponibles: %i",loggersCount);

    for (size_t i = 0; i < loggersCount; i++)
    {
        String tag = loggerList::getLoggerTagByIndex(i);
        uint8_t lvl = loggerList::getLoggerLevelByIndex(i);
        log_w("Logger: [%s]->[%i]", tag, lvl);
    }
}

void setDebugLevels(uint8_t level)
{
    for (size_t i = 0; i < loggerList::getLoggersCount(); i++)
    {
        loggerList::getLoggerByIndex(i)->setLevel(level);
    }
    getDebugLevels();
}