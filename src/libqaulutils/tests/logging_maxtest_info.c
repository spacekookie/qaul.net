/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

/*
 * test logging because of 'What can possibly go wrong?'
 */

#include "qaul/utils/tests.h"

#define QAULLOG_LOGGING_ENABLED
#define QAULLOG_LOGLEVEL_MAX_INFO
#define QAULLOG_LOGLEVEL_DEFAULT LOG_NONE

#define QAULLOG_NO_CONFIG
#include "qaul/utils/logging.h"


#include "inc_leveltest.c"

// ------------------------------------------------------------
int main(int argc, char *argv[])
{

    levelTest();

    return QL_SUCCESS;
}
