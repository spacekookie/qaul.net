Cmake Build Options
===================

Cmake Configuration
-------------------

To configure the cmake build configuration, the following options exist.

General options:

* -DGUI=GUI_TOOKIT_TO_USE
  * Sets graphics user interface framework. By default cmake tries to
    automatically figure out what toolkit to use.
  * The following options exist: NATIVE, CLI, GTK
* -DCOMPILE_MINIMAL=NO
  * Whe set to YES, this option excludes all unnecessary strings etc. from the
    binaries. This is useful when compiling for embedded systems with limited
    memory.
  * Default value is NO.
* -DVOIP=YES
  * When set to NO, the voice over IP library, pjsip, is not compiled and linked
    into qaullib. This is useful, when building qaullib for servers, where voice
    over IP is not necessary.
  * Default value is YES.

Logging options:

* -DQAULLOG_LOGGING_ENABLED=ON|OFF
  * When this option is set to OFF, it does not compile any logging capability into the
    qaullib binary. This is useful when compiling for embedded systems
    with limited memory.
  * This option is optional. Default value is ON.

* -DQAULLOG_DEFAULT_LOGLEVEL=NONE|ERROR|WARN|INFO|DEBUG
  * Sets the default log level.
  * The following log levels exist:
    NONE, ERROR, WARN, INFO, DEBUG
  * This option is optional.
  * Default log level:
    * debug build: DEBUG
    * release build: WARN
* -DQAULLOG_MAX_LOGLEVEL=ERROR|WARN|INFO|DEBUG
  * do not include code for log level above QAULLOG_MAX_LOGLEVEL
  * Defaults:
    * debug build: DEBUG
    * release build: INFO

Android options:

* -DNDK_ROOT=/absolute/path/to/android/NDK
  * Sets the path to the android NDK. This option is mandatory for android
    builds.
* -DEXTRALIB_PATH=/absolute/path/to/android/libraries
  * Sets
* -DANDROID_EABI=EABI_VERSION  
  * Sets the Android EABI version. This version
  * The default EABI version set is 4.9
* -DNDK_LEVEL=9
  * Set the android API target to build for. This is necessary to build for the
    new cyanogenmod ad-hoc java class. This option is optional.
  * Default level is 9.


Make Options
------------

When building the project with make, the following options can be set.

* VERBOSE=1
  * Outputs more verbose build output. This option is useful for debugging.
