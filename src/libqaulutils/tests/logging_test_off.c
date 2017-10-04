/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

/*
 * test logging because of 'What can possibly go wrong?'
 */

#include "qaul/utils/tests.h"

#ifdef QAULLOG_LOGGING_ENABLED
#undef QAULLOG_LOGGING_ENABLED
#endif

#define QAULLOG_NO_CONFIG
#include "qaul/utils/logging.h"


// ------------------------------------------------------------
int main(int argc, char *argv[])
{
    printf("Logging should be turned off.\n");
    QLOG_ERROR("Logged. Logging is OFF.\n");
    QLOG_WARN("Logged. Logging is OFF.\n");
    QLOG_INFO("Logged. Logging is OFF.\n");
    QLOG_DEBUG("Logged. Logging is OFF.\n");
    printf("Is it, isn't it?\n");
    return QL_SUCCESS;
}
