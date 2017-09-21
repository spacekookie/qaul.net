add_executable(tether
		install.c
		tether.c )

find_library(log-lib log)

target_link_libraries(tether
                      libedify
                      hardware_legacy
                      ${log-lib}
                      ${EXTRALIB_PATH}/libwpa_client.so )
