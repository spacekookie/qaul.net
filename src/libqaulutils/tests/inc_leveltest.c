/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

/*
 * test logging because of 'What can possibly go wrong?'
 */

void levelTest()
{

    printf("Logging should be silenced.\n");
    setLogLevel(LOG_NONE);
    LOG_ALL
    printf("Set level error:\n");
    setLogLevel(LOG_ERROR);
    LOG_ALL

    printf("Set level warn:\n");
    setLogLevel(LOG_WARN);
    LOG_ALL

    printf("Set level info:\n");
    setLogLevel(LOG_INFO);
    LOG_ALL

    printf("Set level debug:\n");
    setLogLevel(LOG_DEBUG);
    LOG_ALL

    printf("Everything fine?\n");
}
