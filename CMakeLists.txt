cmake_minimum_required(VERSION 4.1)
project(WizRL C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output binaries to 'bin' (handles MSVC's Debug/Release subfolders too)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

set(SHARED_SOURCES
    include/filehandler.c
    include/game_math.c
)

# 1. Main Executable
add_executable(main main.c ${SHARED_SOURCES})

# 2. Test Executable
add_executable(test test.c ${SHARED_SOURCES})

# Platform-specific Curses setup
if(WIN32)
    # Bundled PDCurses (include/thirdparty/PDCurses-3.9/CMakeLists.txt)
    add_subdirectory(include/thirdparty/PDCurses-3.9)
    target_link_libraries(main PRIVATE pdcurses)
else()
    # Linux / macOS: bundled ncurses (include/thirdparty/ncurses-6.4/CMakeLists.txt)
    add_subdirectory(include/thirdparty/ncurses-6.4)
    target_link_libraries(main PRIVATE ncurses)

    # Link math library on Unix systems
    target_link_libraries(main PRIVATE m)
    target_link_libraries(test PRIVATE m)
endif()
