#include "ESP32LoggingHelper.h"
#include <vector>

loglevels log_level;
std::map<String, logger *> loggers;
std::mutex loggerList::mtx;
std::mutex logger::mtxl;

// logger::logger(uint8_t level)
// {
//     this->_level = level;
//     // memcpy(this->tagName, "", sizeof(this->tagName));

//     char tag[17];
//     sprintf(tag, "logger_%d", (int)this);
//     memcpy(this->tagName, tag, sizeof(this->tagName));
//     // loggers.begin();
//     // loggers.insert(std::make_pair(String(this->tagName), this));
//     // loggerList::addLogger(this); // Add the logger to the loggers array
// }

logger::logger(uint8_t level, char *tag_, bool add)
{
    this->_level = level;
    strncpy(this->tagName, tag_, sizeof(this->tagName));

    if (add)
        loggerList::addLogger(this);
}

void logger::setLevel(uint8_t level)
{
    this->_level = level;
}

uint8_t logger::getLevel()
{
    return this->_level;
}

void logger::setTagName(char *tagName)
{
    memcpy(this->tagName, tagName, sizeof(this->tagName));
    Serial.printf("%s", this->tagName);
}

// char *logger::getTagName()
// {
//     return this->tagName;
// }

bool logger::printV()
{
#ifdef USE_MUTEX
    std::lock_guard<std::mutex> lock(mtxl); // Lock the mutex
#endif
    if (this->_level >= LOGGER_VERBOSE)
    {
        Serial.flush(true);

        Serial.printf("[%s]", this->tagName);
    }

    return (this->_level >= LOGGER_VERBOSE ? true : false);
}
bool logger::printD()
{
#ifdef USE_MUTEX
    std::lock_guard<std::mutex> lock(mtxl); // Lock the mutex
#endif
    if (this->_level >= LOGGER_DEBUG)
    {
        Serial.flush(true);
        Serial.printf("[%s]", this->tagName);
    }
    return (this->_level >= LOGGER_DEBUG ? true : false);
}
bool logger::printI()
{
#ifdef USE_MUTEX
    std::lock_guard<std::mutex> lock(mtxl); // Lock the mutex
#endif
    if (this->_level >= LOGGER_INFO)
    {
        Serial.flush(true);
        Serial.printf("[%s]", this->tagName);
    }

    return (this->_level >= LOGGER_INFO ? true : false);
}
bool logger::printW()
{
#ifdef USE_MUTEX
    std::lock_guard<std::mutex> lock(mtxl); // Lock the mutex
#endif
    if (this->_level >= LOGGER_WARN)
    {
        Serial.flush(true);
        Serial.printf("[%s]", this->tagName);
    }
    return (this->_level >= LOGGER_WARN ? true : false);
}
bool logger::printE()
{
#ifdef USE_MUTEX
    std::lock_guard<std::mutex> lock(mtxl); // Lock the mutex
#endif
    if (this->_level >= LOGGER_ERROR)
    {
        Serial.flush(true);

        Serial.printf("[%s]", this->tagName);
    }
    return (this->_level >= LOGGER_ERROR ? true : false);
}

void loggerList::addLogger(logger *l)
{
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
    loggers[String(l->tagName)] = l;
}

logger *loggerList::getLogger(String tagName)
{
    //   std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

    return loggers[tagName];
}

int loggerList::getLoggersCount()
{
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

    return loggers.size();
}

logger *loggerList::getLoggerByIndex(int index)
{
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

    if (index >= 0 && index < loggers.size())
    {
        auto it = loggers.begin();
        std::advance(it, index);
        return it->second;
    }
    else
    {
        return NULL;
    }
}

const char *loggerList::getLoggerTagByIndex(int index)
{
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

    if (index >= 0 && index < loggers.size())
    {
        auto it = loggers.begin();
        std::advance(it, index);
        return it->first.c_str();
    }
    else
    {
        return NULL;
    }
}

uint8_t loggerList::getLoggerLevelByIndex(int index)
{
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex

    if (index >= 0 && index < loggers.size())
    {
        auto it = loggers.begin();
        std::advance(it, index);
        return it->second->_level;
    }
    else
    {
        return 0;
    }
}