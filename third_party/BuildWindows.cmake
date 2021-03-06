
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

ExternalProject_Add(olsr
    DEPENDS dl_olsr
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/olsr
    URL ${ARCHIVE_DIR}/${OLSR_FILENAME}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND CC=i686-w64-mingw32-gcc make DEBUG=0 OS=win32 olsrd.exe libs
    INSTALL_COMMAND ""
)
