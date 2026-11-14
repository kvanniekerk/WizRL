# ncurses 6.4 uses autotools (./configure && make), not CMake.
# Rewriting its build in CMake isn't practical (it generates headers and
# sources with awk/sh scripts), so we drive its own build with
# ExternalProject and expose the result as a normal CMake target: `ncurses`.
cmake_minimum_required(VERSION 3.14)
project(ncurses_wrapper C)

include(ExternalProject)

# Install to <build>/ncurses rather than under CMAKE_CURRENT_BINARY_DIR:
# that path contains ".../include/thirdparty/...", and ncurses' installer
# rewrites #include <x.h> to <include/x.h> whenever the install path matches
# "/*/include/*", which breaks curses.h.
set(NCURSES_INSTALL_DIR ${CMAKE_BINARY_DIR}/ncurses)
set(NCURSES_LIBRARY     ${NCURSES_INSTALL_DIR}/lib/libncurses.a)
set(NCURSES_INCLUDE_DIR ${NCURSES_INSTALL_DIR}/include)

ExternalProject_Add(ncurses_build
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}
    BINARY_DIR        ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR       ${NCURSES_INSTALL_DIR}
    CONFIGURE_COMMAND sh <SOURCE_DIR>/configure
                          --prefix=<INSTALL_DIR>
                          --without-shared
                          --without-debug
                          --without-ada
                          --without-cxx-binding
                          --without-manpages
                          --without-progs
                          --without-tests
                          --enable-overwrite
                          --disable-db-install
                          # Use the system terminal database at runtime
                          --with-default-terminfo-dir=/usr/share/terminfo
                          --with-terminfo-dirs=/etc/terminfo:/lib/terminfo:/usr/share/terminfo
    BUILD_COMMAND     make
    INSTALL_COMMAND   make install
    BUILD_BYPRODUCTS  ${NCURSES_LIBRARY}
)

# The include dir must exist at configure time for the imported target.
file(MAKE_DIRECTORY ${NCURSES_INCLUDE_DIR})

add_library(ncurses STATIC IMPORTED GLOBAL)
set_target_properties(ncurses PROPERTIES
    IMPORTED_LOCATION             ${NCURSES_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${NCURSES_INCLUDE_DIR}
)
add_dependencies(ncurses ncurses_build)
