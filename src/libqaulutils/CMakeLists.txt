
#################
# the logger part

option(QAULLOG_LOGGING_ENABLED "Enable logging." ON)

if(CMAKE_BUILD_TYPE MATCHES Release)
set(DEFAULT_LEVEL NONE)
set(DEFAULT_MAX WARN)
else()
set(DEFAULT_LEVEL INFO)
set(DEFAULT_MAX DEBUG)
endif()

set (LOGLEVELS NONE ERROR WARN INFO DEBUG)
set (QAULLOG_LOGLEVEL_DEFAULT ${DEFAULT_LEVEL} CACHE STRING "set the default log level (one of ${LOGLEVELS})")
list (FIND LOGLEVELS ${QAULLOG_LOGLEVEL_DEFAULT} RET)
if (${RET} EQUAL -1)
  message(FATAL_ERROR "Please choose which log level set as default +${QAULLOG_LOGLEVEL_DEFAULT}+(one of ${LOGLEVELS})")
endif ()

set (MAXLEVELS ERROR WARN INFO DEBUG)
set (QAULLOG_LOGLEVEL_MAX ${DEFAULT_MAX} CACHE STRING "set the maximum log level (one of ${MAXLEVELS})")
list (FIND MAXLEVELS ${QAULLOG_LOGLEVEL_MAX} RET)
if (${RET} EQUAL -1)
  message(FATAL_ERROR "Please choose which maximum log level to set (one of ${MAXLEVELS})")
endif ()

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/include/qaul/utils/config.h"
)

add_subdirectory (src)

if (BUILD_TESTING)
enable_testing()
add_subdirectory (tests)
endif ()

message(STATUS "*****************************************************************")
message(STATUS "    Logging subsystem: ${QAULLOG_LOGGING_ENABLED}")
if(QAULLOG_LOGGING_ENABLED)
message(STATUS "    Default loglevel: ${QAULLOG_LOGLEVEL_DEFAULT}")
message(STATUS "    Max loglevel: ${QAULLOG_LOGLEVEL_MAX}")
endif()
message(STATUS "*****************************************************************")
