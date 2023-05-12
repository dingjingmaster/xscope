file(GLOB CORE_SRC
        ${CMAKE_SOURCE_DIR}/app/core/global.h
        ${CMAKE_SOURCE_DIR}/app/core/core-log.h

        ${CMAKE_SOURCE_DIR}/app/core/event.h
        ${CMAKE_SOURCE_DIR}/app/core/event.c

        ${CMAKE_SOURCE_DIR}/app/core/server.h
        ${CMAKE_SOURCE_DIR}/app/core/server.c

        ${CMAKE_SOURCE_DIR}/app/core/xproto.h
        ${CMAKE_SOURCE_DIR}/app/core/xproto.c

        ${CMAKE_SOURCE_DIR}/app/core/xtype-builtin.h
        ${CMAKE_SOURCE_DIR}/app/core/xtype-builtin.c

        ${CMAKE_SOURCE_DIR}/app/core/print/print-type.h
        ${CMAKE_SOURCE_DIR}/app/core/print/print-type.c

        ${CMAKE_SOURCE_DIR}/app/core/decode/decode_x11.h
        ${CMAKE_SOURCE_DIR}/app/core/decode/decode_x11.c

        )
include_directories(${CMAKE_SOURCE_DIR}/app/core)