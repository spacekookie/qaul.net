/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

#define LOGGER_IMPLEMENTATION

#include "qaul/utils/logging.h"

#ifdef QAULLOG_LOGGING_ENABLED

loglevel_t getLogLevel(void) {
    return loglevel;
}

// returns the previous log level
loglevel_t setLogLevel(loglevel_t newloglevel) {
    if (loglevel == newloglevel) return loglevel;
    loglevel_t oldLogLevel = loglevel;
    loglevel = newloglevel;
    return oldLogLevel;
}

#endif // QAULLOG_LOGGING_ENABLED
