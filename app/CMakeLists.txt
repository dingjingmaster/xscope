file(GLOB X_SCOPE_SRC
        ${CMAKE_SOURCE_DIR}/app/x11.h
        ${CMAKE_SOURCE_DIR}/app/proto.h
        ${CMAKE_SOURCE_DIR}/app/global.h

        ${CMAKE_SOURCE_DIR}/app/fd.h
        ${CMAKE_SOURCE_DIR}/app/fd.c

        ${CMAKE_SOURCE_DIR}/app/scope.h
        ${CMAKE_SOURCE_DIR}/app/scope.c

        ${CMAKE_SOURCE_DIR}/app/common.h
        ${CMAKE_SOURCE_DIR}/app/common.c
        )

add_executable(xscope main.c ${X_SCOPE_SRC})