cmake_minimum_required(VERSION 3.4.1)

include(ExternalProject)

option(ANDROID_REWRITE_HACK_LIBONLY "If ON only libqaul.so is build" ON)

set(PORT "ANDROID")

find_library(log-lib log)
find_library(android-lib android)


if(NOT ANDROID_REWRITE_HACK_LIBONLY)
# find_package(BISON)
# find_package(FLEX)

# set(CMAKE_C_STANDARD 99)

add_subdirectory(edify)
add_subdirectory(hardware_legacy)
add_subdirectory(wificonfig)
add_subdirectory(tether)

add_library(nativetask SHARED
            android_tether_system_NativeTask.c )

endif(NOT ANDROID_REWRITE_HACK_LIBONLY)

# TODO remove, fix warnings. If not possible, bump version to 3.x
# somthing newish is anyways required for cross bild..
cmake_policy(SET CMP0054 OLD)

# add_subdirectory(../../../../../src/libqaulutils qaul/libqaulutils)
# add_subdirectory(../../../../../src/libqaulconnector qaul/libqaulconnector)
# add_subdirectory(../../../../../third_party qaul/third_party)
# add_subdirectory(../../../../../src/libqaul qaul/libqaul)

add_subdirectory(../../src/libqaulutils qaul/libqaulutils)
add_subdirectory(../../src/libqaulconnector qaul/libqaulconnector)
add_subdirectory(../../third_party qaul/third_party)
add_subdirectory(../../src/libqaul qaul/libqaul)

# add_subdirectory(src/libqaulutils ${CMAKE_BINARY_DIR}/xxsrc/xxlibqaulutils)
# add_subdirectory(src/libqaulconnector ${CMAKE_BINARY_DIR}/xxsrc/xxlibqaulconnector)
# add_subdirectory(third_party ${CMAKE_BINARY_DIR}/xxthird_party)
# add_subdirectory(src/libqaul ${CMAKE_BINARY_DIR}/xxsrc/xxlibqaul)

# add_subdirectory(../../src/libqaulutils)
# add_subdirectory(src/libqaulconnector)
# add_subdirectory(third_party)
# add_subdirectory(src/libqaul)

# set(JNI_SRC ${CMAKE_SOURCE_DIR}/android/app/src/main/jni)
set(JNI_SRC ${CMAKE_SOURCE_DIR}/src/main/jni)

add_library(reallibqaul SHARED ${JNI_SRC}/net_qaul_qaul_NativeQaul.c)
target_link_libraries(reallibqaul
                      libqaul
                      android
                      log)
# target_include_directories(libcuckoo-static PUBLIC "include")
set_target_properties(reallibqaul PROPERTIES OUTPUT_NAME "qaul")


message(STATUS "========== VARIABLES ==========")
#get_cmake_property(vs VARIABLES)
#foreach(v ${vs})
#  message(STATUS "${v}='${${v}}'")
#endforeach()
message(STATUS "========== VARIABLES ==========")
message(STATUS "HACK_MBEDTLS_INSTALL_DIR ${HACK_MBEDTLS_INSTALL_DIR}")