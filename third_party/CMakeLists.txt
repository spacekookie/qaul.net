set(CommonCMakeArgs
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

if (${PORT} STREQUAL "ANDROID")
    set(CommonCMakeArgs
        ${CommonCMakeArgs}
        -DANDROID_TOOLCHAIN=${ANDROID_TOOLCHAIN}
        -DANDROID_ARM_MODE=${ANDROID_ARM_MODE}
        -DANDROID_ABI=${ANDROID_ABI}
    )
endif ()

set(MbedTlsCMakeArgs
    ${CommonCMakeArgs}
	-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external/mbedtls
	-DENABLE_PROGRAMS=OFF

)

if (${PORT} STREQUAL "WINDOWS")
set(MbedTlsCMakeArgs
	${MbedTlsCMakeArgs}
	-DENABLE_TESTING=OFF
)
endif ()

ExternalProject_Add(mbedtls
	#UPDATE_DISCONNECTED 1
	GIT_SUBMODULES mbedtls
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/mbedtls
	DOWNLOAD_COMMAND git submodule update
	DOWNLOAD_DIR ${PROJECT_SOURCE_DIR}
	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls
	BINARY_DIR ${PROJECT_BINARY_DIR}/external/mbedtls-build
	STAMP_DIR ${PROJECT_BINARY_DIR}/external/mbedtls-stamp
	TMP_DIR ${PROJECT_BINARY_DIR}/external/mbedtls-tmp
	INSTALL_DIR ${PROJECT_BINARY_DIR}/external
	BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/external/mbedtls/lib/libmbedcrypto.a
	CMAKE_ARGS ${MbedTlsCMakeArgs}
)

set(LibCuckooCMakeArgs
    ${CommonCMakeArgs}
	-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external/libcuckoo
)

ExternalProject_Add(libcuckoo
	#UPDATE_DISCONNECTED 1
	GIT_SUBMODULES libcuckoo
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libcuckoo
	DOWNLOAD_COMMAND git submodule update
	DOWNLOAD_DIR ${PROJECT_SOURCE_DIR}
	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libcuckoo
	BINARY_DIR ${PROJECT_BINARY_DIR}/external/libcuckoo-build
	STAMP_DIR ${PROJECT_BINARY_DIR}/external/libcuckoo-stamp
	TMP_DIR ${PROJECT_BINARY_DIR}/external/libcuckoo-tmp
	INSTALL_DIR ${PROJECT_BINARY_DIR}/external
	BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/external/libcuckoo/lib/libcuckoo.a
	CMAKE_ARGS ${LibCuckooCMakeArgs}
)

set (ARCHIVE_DIR ${PROJECT_SOURCE_DIR}/archives)

set (PJSIP_CONFIGURE_OPTIONS "--disable-opus")

set (PJSIP_VERSION "2.6")
set (PJSIP_FILENAME "pjproject-${PJSIP_VERSION}.tar.bz2")
set (PJSIP_URL "http://www.pjsip.org/release/${PJSIP_VERSION}/${PJSIP_FILENAME}")
set (PJSIP_MD5 "c347a672679e7875ce572e18517884b2")

set (OLSR_VERSION "0.6.8.1")
set (OLSR_FILENAME "olsrd-${OLSR_VERSION}.tar.bz2")
set (OLSR_URL "http://www.olsr.org/releases/0.6/${OLSR_FILENAME}")
set (OLSR_MD5 "8cfc977be7e10224ccbb0f943675b7fa")

set (PORTFWD_FILENAME "master.tar.gz")
set (PORTFWD_URL "http://github.com/qaul/portfwd/archive/${PORTFWD_FILENAME}")
set (PORTFWD_MD5 "21385143f85a2a0512804a1cafa145b1")

add_custom_target(dl_portfwd
    COMMAND ${CMAKE_COMMAND} -DDL_URL=${PORTFWD_URL} -DDL_FILENAME=${ARCHIVE_DIR}/${PORTFWD_FILENAME} -DDL_MD5=${PORTFWD_MD5} -P ${CMAKE_CURRENT_SOURCE_DIR}/download.cmake 
)

add_custom_target(dl_pjsip
    COMMAND ${CMAKE_COMMAND} -DDL_URL=${PJSIP_URL} -DDL_FILENAME=${ARCHIVE_DIR}/${PJSIP_FILENAME} -DDL_MD5=${PJSIP_MD5} -P ${CMAKE_CURRENT_SOURCE_DIR}/download.cmake 
)

add_custom_target(dl_olsr
    COMMAND ${CMAKE_COMMAND} -DDL_URL=${OLSR_URL} -DDL_FILENAME=${ARCHIVE_DIR}/${OLSR_FILENAME} -DDL_MD5=${OLSR_MD5} -P ${CMAKE_CURRENT_SOURCE_DIR}/download.cmake 
)

option(Raspberry "Raspberry" 0)

if (${PORT} STREQUAL "ANDROID")
    include(BuildAndroid.cmake)
elseif (${PORT} STREQUAL "OPENWRT")
    include(BuildOpenWrt.cmake)
elseif (${PORT} STREQUAL "WINDOWS")
    include(BuildWindows.cmake)
elseif (${PORT} STREQUAL "OSX")
    include(BuildOSX.cmake)
elseif (${PORT} STREQUAL "LINUX")
    if (Raspberry)
	include(BuildRaspberry.cmake)
    else ()
	include(BuildLinux.cmake)
    endif ()
else ()
    message(FATAL_ERROR "Unknown PORT ${PORT}.")
endif ()
