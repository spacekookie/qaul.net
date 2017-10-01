cmake_minimum_required (VERSION 3.2)

project (qaul)

include (CTest)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	if (APPLE)
		set (CMAKE_INSTALL_PREFIX "/Library/qaul.net" CACHE PATH "qaul.net install prefix" FORCE)
	endif ()
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include (ExternalProject)

# The version number.
set (QAUL_VERSION_MAJOR 1)
set (QAUL_VERSION_MINOR 0)
set (QAUL_VERSION_PATCH 0)
set (QAUL_VERSION_SUFFIX "beta5")
set (QAUL_VERSION "${QAUL_VERSION_MAJOR}.${QAUL_VERSION_MINOR}.${QAUL_VERSION_PATCH}.${QAUL_VERSION_SUFFIX}")
set (QAUL_ANDROID_VERSION_CODE "1" CACHE STRING "Android versions code (build number)")
set (QAUL_ANDROID_VERSION_NAME "${QAUL_VERSION}" CACHE STRING "Android versions name (displayed version string")

# install configuration
set (QAUL_DESKTOPDIR "/usr/share/applications" CACHE STRING "choose install location for the .desktop file")
set (QAUL_ICONDIR "${CMAKE_INSTALL_PREFIX}/lib/qaul/icons" CACHE STRING "choose install location for the aplication icon file(s)")
set (QAUL_BINDIR "NONE" CACHE STRING "if set a wrapper shell script will be installed here")

# determine the GUI
set(ALL_GUIS CLI NATIVE GTK QT5)
STRING (TOUPPER "${GUI}" GUI)
set(GUI "DEFAULT" CACHE STRING "Choose which qaul GUI to build (one of ${ALL_GUIS})")

# readjust defaults
if (${GUI} STREQUAL "DEFAULT")
  if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set (GUI GTK)
  else ()
    set (GUI NATIVE)
  endif ()
endif ()

# set the name for the ui executable
if (${GUI} STREQUAL "GTK")
    set (GUINAME "qaul-gtk")
elseif (${GUI} STREQUAL "QT5")
    set (GUINAME "qaul-qt5")
elseif (${GUI} STREQUAL "CLI")
    set (GUINAME "qaul-cli")
else ()
    set (GUINAME "qaul")
endif ()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set (GUINAME "${GUINAME}.exe")
endif ()

list(FIND ALL_GUIS ${GUI} RET)
if (${RET} EQUAL -1)
  message(FATAL_ERROR "Please choose which qaul GUI to build (one of ${ALL_GUIS})")
endif ()

# What package to build
set(ALL_PKGFORMAT AUTO NSIS TGZ RPM DEB)
set(PKGFORMAT "AUTO" CACHE STRING "select what type of package should be build (one of ${ALL_PKGFORMAT})")

# Cpack general Installer settings
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/Licenses/qaul.net_license.txt)
set(CPACK_PACKAGE_VENDOR "qaul.net community")
set(CPACK_PACKAGE_VERSION_MAJOR ${QAUL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${QAUL_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${QAUL_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_SUFFIX ${QAUL_VERSION_SUFFIX})
set(CPACK_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CPACK_PACKAGE_VERSION_SUFFIX})

# configure a header file to pass some of the CMake settings
# to the source code
string(TOUPPER ${CMAKE_SYSTEM_NAME} PORT)
configure_file (
  "${PROJECT_SOURCE_DIR}/include/QaulConfig.h.in"
  "${PROJECT_BINARY_DIR}/include/QaulConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find QaulConfig.h
include_directories ("${PROJECT_BINARY_DIR}/include")

include(cmake/Build${CMAKE_SYSTEM_NAME}.cmake)

add_subdirectory (third_party)
add_subdirectory (src/olsrd-plugin)

add_subdirectory (src/libqaulutils)
add_subdirectory (src/libqaulconnector)
add_subdirectory (src/libqaul)

# on linux always build the cli client
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND NOT ${GUI} STREQUAL "CLI")
    add_subdirectory (src/client/cli)
endif ()

if (${GUI} STREQUAL "NATIVE")
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_subdirectory (src/client/osx)
    elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    # add_subdirectory (src/client/win)
    elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    # have its own
    else ()
    message(FATAL_ERROR "Dont know how to build UI '${GUI}' on  '${CMAKE_SYSTEM_NAME}'")
    endif ()
elseif (${GUI} STREQUAL "CLI")
    add_subdirectory (src/client/cli)
elseif (${GUI} STREQUAL "GTK")
    add_subdirectory (src/client/gtk)
elseif (${GUI} STREQUAL "QT5")
    add_subdirectory (src/client/qt5)
else ()
    message(FATAL_ERROR "Dont know how to build ui '${GUI}'")
endif ()

if (${CMAKE_SYSTEM_NAME} STREQUAL "LINUX")
  option (LINUXDAEMON "Use Linux daemon" ON)
else ()
  option (LINUXDAEMON "Use Linux daemon" OFF)
endif ()

# build qauld the qaul.net daemon
if (LINUXDAEMON)
    add_subdirectory (src/daemon/linux)
endif ()

# Add uninstall target
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake")

# final status summary report
message(STATUS "#############################################")
message(STATUS "  qaul seems to be successfully configured.")
message(STATUS "    Building for platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "    Building GUI: ${GUI}")
message(STATUS "    Arm/Raspberry patches enabled: ${Raspberry}")
message(STATUS "    Qaul executable: ${GUINAME}")
message(STATUS "*****************************************************************")
message(STATUS "To build the project execute the command")
message(STATUS "        make")
if (BUILD_TESTING)
    message(STATUS "To run the tests type")
    message(STATUS "        ctest --output-on-failure")
endif()
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "To install the project type the command")
    message(STATUS "        sudo make install")
    message(STATUS "To uninstall the project type the command")
    message(STATUS "        sudo make uninstall")
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message(STATUS "Generate a DMG installer image")
    message(STATUS "        ./make_dmg.sh")
    message(STATUS "To install qaul.net build on your local system type")
    message(STATUS "        sudo make install")
    message(STATUS "To uninstall qaul.net build from your local system type")
    message(STATUS "        sudo make uninstall")
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message(STATUS "To build Visual Studio project files")
    message(STATUS "        mkdir src/client/win/build")
    message(STATUS "        cd build")
    message(STATUS "        cmake..")
    message(STATUS "To be able to run qaul.net from within Visual Studio,")
    message(STATUS "set the qaul project as your start up project in Visual Studio:")
    message(STATUS "Right-click on the qaul project icon and select: Set as StartUp Project.")
endif()
message(STATUS "*****************************************************************")
