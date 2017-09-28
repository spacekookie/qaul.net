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


# build all the .a's
add_subdirectory(../../src/libqaulutils qaul/libqaulutils)
add_subdirectory(../../src/libqaulconnector qaul/libqaulconnector)
add_subdirectory(../../third_party qaul/third_party)
add_subdirectory(../../src/libqaul qaul/libqaul)

# the magic part: libqaul.so

# old api
set(JNI_SOURCE_DIR_LEGACY ${CMAKE_SOURCE_DIR}/src/main/jni)


# new api

set(JNI_BASE_DIR ${CMAKE_SOURCE_DIR}/src)

set(JNI_SOURCE_FILES "")

#macro voodoo for composing .so per flavor
macro(add_auto_src file_name)
  if(EXISTS ${JNI_BASE_DIR}/${QFLAVOR_NAME}/jni/${file_name})
    set(JNI_SOURCE_FILES
         ${JNI_SOURCE_FILES}
         ${JNI_BASE_DIR}/${QFLAVOR_NAME}/jni/${file_name})
    message(STATUS "#!## flavor")
  else()
  endif()
endmacro(add_auto_src)

macro(add_flavor_src flavor_name file_name)
  if(${flavor_name} STREQUAL ${QFLAVOR_NAME})
    add_auto_src(${file_name})
  endif()
endmacro(add_flavor_src)

macro(add_main_src file_name)
    set(JNI_SOURCE_FILES
        ${JNI_SOURCE_FILES}
        ${JNI_BASE_DIR}/main/jni/${file_name})
endmacro(add_main_src)

#add_main_src(test.c)
#add_auto_src(test.c)
#add_flavor_src(noroot test.c)

add_library(reallibqaul SHARED
               ${JNI_SOURCE_DIR_LEGACY}/net_qaul_qaul_NativeQaul.c
               ${JNI_SOURCE_FILES})

# find generated jni headers
target_include_directories(reallibqaul PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include)

target_link_libraries(reallibqaul
                      libqaul
                      android
                      log)
set_target_properties(reallibqaul PROPERTIES OUTPUT_NAME "qaul")

# be verbose what we are building for
message(STATUS "#############################################")
message(STATUS "  Building for platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  CMAKE_ANDROID_ARCH_ABI=${CMAKE_ANDROID_ARCH_ABI}")
message(STATUS "  CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "  ANDROID_TOOLCHAIN=${ANDROID_TOOLCHAIN}")
message(STATUS "  ANDROID_ABI=${ANDROID_ABI}")
message(STATUS "  ANDROID_ARM_MODE=${ANDROID_ARM_MODE}")
message(STATUS "  Default loglevel: ${QAUL_DEFAULT_LOGLEVEL}")
message(STATUS "#############################################")
