file(GLOB CORE_SRC
        ${CMAKE_SOURCE_DIR}/app/core/global.h
        ${CMAKE_SOURCE_DIR}/app/core/core-log.h

        ${CMAKE_SOURCE_DIR}/app/core/event.h
        ${CMAKE_SOURCE_DIR}/app/core/event.c

        ${CMAKE_SOURCE_DIR}/app/core/server.h
        ${CMAKE_SOURCE_DIR}/app/core/server.c

        ${CMAKE_SOURCE_DIR}/app/core/xserver.h
        ${CMAKE_SOURCE_DIR}/app/core/xserver.c
        )
include_directories(${CMAKE_SOURCE_DIR}/app/core)