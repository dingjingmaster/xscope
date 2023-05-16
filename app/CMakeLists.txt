file(GLOB X_SCOPE_SRC
        )

include(core/core.cmake)

add_executable(xscope main.c ${X_SCOPE_SRC} ${CORE_SRC})
target_link_libraries(xscope ${GIO_LIBRARIES} ${GLIB_LIBRARIES})
target_include_directories(xscope
        PUBLIC ${GIO_INCLUDE_DIRS}
        PUBLIC ${GLIB_INCLUDE_DIRS}
        )