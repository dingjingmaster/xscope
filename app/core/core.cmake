file(GLOB CORE_SRC
        ${CMAKE_SOURCE_DIR}/app/core/core-log.h

        ${CMAKE_SOURCE_DIR}/app/core/event.h
        ${CMAKE_SOURCE_DIR}/app/core/event.c

        ${CMAKE_SOURCE_DIR}/app/core/tools.h
        ${CMAKE_SOURCE_DIR}/app/core/tools.c

        ${CMAKE_SOURCE_DIR}/app/core/server.h
        ${CMAKE_SOURCE_DIR}/app/core/server.c

        ${CMAKE_SOURCE_DIR}/app/core/global.h
        ${CMAKE_SOURCE_DIR}/app/core/global.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xproto.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xproto.c

        ${CMAKE_SOURCE_DIR}/app/core/conn-context.h
        ${CMAKE_SOURCE_DIR}/app/core/conn-context.c

        ${CMAKE_SOURCE_DIR}/app/core/io/io.h
        ${CMAKE_SOURCE_DIR}/app/core/io/io.c

#        ${CMAKE_SOURCE_DIR}/app/core/print/print-type.h
#        ${CMAKE_SOURCE_DIR}/app/core/print/print-type.c

        ${CMAKE_SOURCE_DIR}/app/core/decode/decode.h
        ${CMAKE_SOURCE_DIR}/app/core/decode/decode.c

        ${CMAKE_SOURCE_DIR}/app/core/decode/decode_x11.h
        ${CMAKE_SOURCE_DIR}/app/core/decode/decode_x11.c

        ${CMAKE_SOURCE_DIR}/app/core/decode/decode-xclient.h
        ${CMAKE_SOURCE_DIR}/app/core/decode/decode-xclient.c

        ${CMAKE_SOURCE_DIR}/app/core/decode/decode-xserver.h
        ${CMAKE_SOURCE_DIR}/app/core/decode/decode-xserver.c

        ${CMAKE_SOURCE_DIR}/app/core/decode/decode-extensions.h
        ${CMAKE_SOURCE_DIR}/app/core/decode/decode-extensions.c


        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-set.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-set.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-atom.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-atom.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-record.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-record.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-common.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-common.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-values.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-values.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-builtin.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-builtin.c

        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-enumerated.h
        ${CMAKE_SOURCE_DIR}/app/core/proto/xtype-enumerated.c

        )
include_directories(${CMAKE_SOURCE_DIR}/app/core)