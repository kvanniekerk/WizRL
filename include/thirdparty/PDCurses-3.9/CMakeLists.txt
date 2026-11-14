# PDCurses 3.9 - Windows console (wincon) port, built as a static library.
cmake_minimum_required(VERSION 3.14)
project(pdcurses C)

option(PDCURSES_WIDE "Build PDCurses with wide-character (Unicode) support" OFF)

file(GLOB PDCURSES_CORE_SOURCES   ${CMAKE_CURRENT_SOURCE_DIR}/pdcurses/*.c)
file(GLOB PDCURSES_WINCON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/wincon/*.c)

add_library(pdcurses STATIC ${PDCURSES_CORE_SOURCES} ${PDCURSES_WINCON_SOURCES})

# curses.h / panel.h live in the root of this folder; anything linking
# pdcurses gets that include path automatically.
target_include_directories(pdcurses
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/wincon
)

if(PDCURSES_WIDE)
    target_compile_definitions(pdcurses PUBLIC PDC_WIDE)
endif()

if(MSVC)
    target_compile_definitions(pdcurses PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
