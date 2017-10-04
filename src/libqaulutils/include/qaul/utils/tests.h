/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

#ifndef _TESTS_H
#define _TESTS_H

/***
 * macros and defines used by tests only
 ***/

#include <stdio.h>
#include "qaul/utils/defines.h"
#define FAIL(M) printf(M); return(QL_ERROR);

#define LOG_ALL QLOG_ERROR("ERROR Logged.\n"); \
QLOG_WARN("WARNING Logged.\n"); \
QLOG_INFO("INFO Logged.\n"); \
QLOG_DEBUG("DEBUG Logged.\n"); \

#endif // _TESTS_H
