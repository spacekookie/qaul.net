
if (VOIP)
ExternalProject_Add(pjsip
    DEPENDS dl_pjsip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/pjsip
    URL ${ARCHIVE_DIR}/${PJSIP_FILENAME}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 -t -N -i ${CMAKE_CURRENT_SOURCE_DIR}/pjsip.patch
    CONFIGURE_COMMAND ./aconfigure --prefix=${CMAKE_INSTALL_PREFIX} --disable-ffmpeg --disable-ssl --disable-video --disable-libwebrtc ${PJSIP_CONFIGURE_OPTIONS}
    BUILD_COMMAND make dep COMMAND make
    INSTALL_COMMAND ""
)
endif()

if (PORTFWD)
ExternalProject_Add(portfwd
    DEPENDS dl_portfwd
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/portfwd
    URL ${ARCHIVE_DIR}/${PORTFWD_FILENAME}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 -t -N -i ${CMAKE_CURRENT_SOURCE_DIR}/portfwd.patch
    CONFIGURE_COMMAND "./bootstrap" COMMAND "./configure"
    BUILD_COMMAND make
    INSTALL_COMMAND ""
)
endif()

if (NOT USE_SYSTEM_OLSRD)
ExternalProject_Add(olsr
    DEPENDS dl_olsr
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/olsr
    URL ${ARCHIVE_DIR}/${OLSR_FILENAME}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make DEBUG=0 olsrd libs
    INSTALL_COMMAND ""
)
endif()
