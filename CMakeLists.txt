project(xscope LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.5)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(
        -w -g
        -D PACKAGE_NAME=\\"${PROJECT_NAME}\\"
        -D G_LOG_DOMAIN=\\"${PROJECT_NAME}\\"
        -D PACKAGE_VERSION=\\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\\")

find_package (PkgConfig)

pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_check_modules(LIBCURL REQUIRED libcurl)
pkg_check_modules(THREAD REQUIRED gthread-2.0)
pkg_check_modules(PROTOBUF REQUIRED protobuf)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

cmake_host_system_information(RESULT OS QUERY OS_NAME)
MESSAGE(STATUS "OS name: ${OS}")

cmake_host_system_information(RESULT RELEASE QUERY OS_RELEASE)
MESSAGE(STATUS "OS release: ${RELEASE}")

execute_process(COMMAND bash -c "qmake --version | grep -i 'qt version' | awk '{print $4}' | tr '\n' ' '|sed 's/ //g'" OUTPUT_VARIABLE CUR_QT_VERSION)
MESSAGE(STATUS "Qt Version: ${CUR_QT_VERSION}")

execute_process(COMMAND uname -m OUTPUT_VARIABLE OS_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
MESSAGE(STATUS "OS arch: '${OS_ARCH}'")

execute_process(COMMAND bash -c "cat /etc/os-release|grep -E '^NAME'|awk -F'=' '{print $2}'|sed 's/\"//g'|tr '\n' ' '|sed 's/ //g'"
        OUTPUT_VARIABLE DISTRIB)
MESSAGE(STATUS "OS distribute: '${DISTRIB}'")

add_subdirectory(app)
