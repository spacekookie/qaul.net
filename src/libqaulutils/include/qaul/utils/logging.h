/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

/**
 * Logging macros for qaul.net.
 *
 * The following log levels exist:
 * 	NONE
 * 	ERROR
 * 	WARN
 * 	INFO
 * 	DEBUG
 *
 * Default log level when compiling is DEBUG.
 * The messages can be included/excluded during compile time by setting a log level.
 *
 * Cmake build options:
 * -DQAUL_LOG_ENABLE=NO             (Disable all logging. Default is YES.)
 * -DQAUL_LOG_DEFAULTLEVEL=LOGLEVEL (Set log level to one of the available log levels. Default log level is DEBUG.)
 */

#ifndef __QAULLIB_UTILS_LOGGING_H
#define __QAULLIB_UTILS_LOGGING_H

#ifndef QAULLOG_NO_CONFIG
#include "qaul/utils/config.h"
#endif

#ifndef QAULLOG_LOGGING_ENABLED

// logging is turnend off, so define some dummies and bail out.
#define QLOG_DEBUG(...)
#define QLOG_INFO(...)
#define QLOG_WARN(...)
#define QLOG_ERROR(...)

#else

#ifdef __ANDROID__
#include <android/log.h>
#else
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#endif

/**
 * The following log levels exist:
 *
 * NONE  => LOG_NONE  => Nothing will be logged at all.
 * ERROR => LOG_ERROR => Log as error.
 *                       Only ERROR will be logged.
 * WARN  => LOG_WARN  => Log as warning.
 *                       ERROR and WARN will be logged.
 * INFO  => LOG_INFO  => Log as information.
 *                       ERROR, WARN and INFO will be logged.
 * DEBUG => LOG_DEBUG => Log as debug message.
 *                       ERROR, WARN, INFO and DEBUG will be logged.
 */

#define LOG_NONE  0
#define LOG_ERROR 1
#define LOG_WARN  2
#define LOG_INFO  3
#define LOG_DEBUG 4

#ifdef QAULLOG_LOGLEVEL_MAX_ERROR
#define QAULLOG_LOGLEVEL_MAX 1
#elif defined QAULLOG_LOGLEVEL_MAX_WARN
#define QAULLOG_LOGLEVEL_MAX 2
#elif defined QAULLOG_LOGLEVEL_MAX_INFO
#define QAULLOG_LOGLEVEL_MAX 3
#elif defined QAULLOG_LOGLEVEL_MAX_DEBUG
#define QAULLOG_LOGLEVEL_MAX 4
#else
#error "Something to fix"
#endif

typedef int loglevel_t;

#ifdef LOGGER_IMPLEMENTATION

#ifndef QAULLOG_LOGLEVEL_DEFAULT
#define QAULLOG_LOGLEVEL_DEFAULT LOG_DEBUG
#endif

loglevel_t loglevel = QAULLOG_LOGLEVEL_DEFAULT;

const char *const LOG_LEVEL_NAMES[] = {
    "NONE",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG"
};
#else // LOGGER_IMPLEMENTATION
extern loglevel_t loglevel;
extern const char *const LOG_LEVEL_NAMES[];
#endif // LOGGER_IMPLEMENTATION

#define Ql_levelname(M) LOG_LEVEL_NAMES[M]


/**
 * Log message as error message.
 *
 * This message will be shown, when the program is compiled with either of these log levels:
 * ERROR, WARN, INFO or DEBUG.
 *
 * usage:
 * 	Ql_log_error("My Error message");
 * 	Ql_log_error("My %s message number %i", "error", 2);
 */
#if LOG_ERROR > QAULLOG_LOGLEVEL_MAX
#define QLOG_ERROR(...)
#else
#define QLOG_ERROR(M, ...) if ( LOG_ERROR <= loglevel ) QLOG_LOGLINE(LOG_ERROR, M , ##__VA_ARGS__)
#endif


/**
 * Log message as error message.
 *
 * This message will be shown, when the program is compiled with either of these log levels:
 * WARN, INFO or DEBUG.
 *
 * usage:
 * 	Ql_log_warn("My Error message");
 * 	Ql_log_warn("My %s message number %i", "warn", 2);
 */
#if LOG_WARN > QAULLOG_LOGLEVEL_MAX
#define QLOG_WARN(...)
#else
#define QLOG_WARN(M, ...) if ( LOG_WARN <= loglevel ) QLOG_LOGLINE(LOG_WARN, M , ##__VA_ARGS__)
#endif


/**
 * Log message as error message.
 *
 * This message will be shown, when the program is compiled with either of these log levels:
 * INFO or DEBUG.
 *
 * usage:
 * 	Ql_log_info("My Error message");
 * 	Ql_log_info("My %s message number %i", "info", 2);
 */
#if LOG_INFO > QAULLOG_LOGLEVEL_MAX
#define QLOG_INFO(...)
#else
#define QLOG_INFO(M, ...) if ( LOG_INFO <= loglevel ) QLOG_LOGLINE(LOG_INFO, M , ##__VA_ARGS__)
#endif

/**
 * Log message as debug message.
 *
 * This message will be shown, when the program is compiled with log level
 * DEBUG.
 *
 * usage:
 * 	Ql_log_debug("My debug message");
 * 	Ql_log_debug("My %s message number %i", "debug", 2);
 */
#if LOG_DEBUG > QAULLOG_LOGLEVEL_MAX
#define QLOG_DEBUG(...)
#else
#define QLOG_DEBUG(M, ...) if ( LOG_DEBUG == loglevel ) QLOG_LOGLINE(LOG_DEBUG, M, ##__VA_ARGS__)
#endif

#ifdef __ANDROID__
#define QLOG_LOGLINE(L, M, ...) { \
    __android_log_print(ANDROID_ ## L , __FILE__, "(%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
} \

#else
#define QLOG_LOGLINE(L, M, ...) { \
    char date[20]; \
    struct timeval tv; \
    gettimeofday(&tv, NULL); \
    strftime(date, sizeof(date) / sizeof(*date), "%Y-%m-%dT%H:%M:%S", gmtime(&tv.tv_sec)); \
    fprintf(stderr, "%s.%03ldZ [%s] (%s:%d) " M "\n", &date[0], (tv.tv_usec/1000), Ql_levelname( L ), __FILE__, __LINE__, ##__VA_ARGS__); \
} \

#endif

#define Ql_check(A, M, ...) if(!(A)) { Ql_log_error(M, ##__VA_ARGS__); errno=0; goto Ql_error; }

#define Ql_sentinel(M, ...)  { Ql_log_error(M, ##__VA_ARGS__); errno=0; goto Ql_error; }

#define Ql_check_mem(A) Ql_check((A), "Out of memory.")

#define Ql_check_debug(A, M, ...) if(!(A)) { ql_log_debug(M, ##__VA_ARGS__); errno=0; goto Ql_error; }

loglevel_t getLogLevel(void);
loglevel_t setLogLevel(loglevel_t newloglevel);

#endif // QAULLOG_LOGGING_ENABLED

#endif // __QAULLIB_UTILS__LOGGING_H
