#ifndef mylogging_h
#define mylogging_h

#include "Arduino.h"
#include <map>
#include <mutex>

// #define USE_MUTEX //Habilita el uso de un mutex previo a cada print. en implementaciones multithread puede ralentizar la ejecucion de todo!

typedef enum
{
    LOGGER_NONE,   /*!< No log output */
    LOGGER_ERROR,  /*!< Critical errors, software module can not recover on its own */
    LOGGER_WARN,   /*!< Error conditions from which recovery measures have been taken */
    LOGGER_INFO,   /*!< Information messages which describe normal flow of events */
    LOGGER_DEBUG,  /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    LOGGER_VERBOSE /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} loglevels;

extern loglevels log_level;

class logger
{
public:
    // logger(uint8_t level);
    logger(uint8_t level, char *tagName, bool add = false);
    void setTagName(char *tagName);
    // char *getTagName();
    void setLevel(uint8_t level);
    uint8_t getLevel();
    bool printV();
    bool printD();
    bool printI();
    bool printW();
    bool printE();

    friend class loggerList;
    static std::mutex mtxl;

private:
    uint8_t _level;
    char tagName[17];
    bool printTag = true;
};


extern std::map<String, logger *> loggers;

class loggerList
{
public:
    static void addLogger(logger *l);
    static logger *getLogger(String tagName);
    static logger* getLoggerByIndex(int index);
    static const char* getLoggerTagByIndex(int index);
    static uint8_t getLoggerLevelByIndex(int index);
    static int getLoggersCount();
    static std::mutex mtx;

};

#endif