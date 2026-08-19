cmake_minimum_required(VERSION 3.20)

project(
    ASCIIPlayer
    VERSION 0.1.0
    DESCRIPTION "ASCII Player"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    asciiplayer
    src/main.c
    src/audio.c
    src/decoder.c
    src/fetcher.c
    src/player.c
    src/renderer.c
    src/terminal.c
    src/cli.c
)

target_include_directories(asciiplayer
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(asciiplayer
    PRIVATE
        _POSIX_C_SOURCE=200809L
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(FFMPEG REQUIRED
    libavformat
    libavcodec
    libavutil
    libswscale
)

target_link_libraries(asciiplayer
    PRIVATE
        ${FFMPEG_LIBRARIES}
)

target_compile_options(asciiplayer
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

install(TARGETS asciiplayer
    RUNTIME DESTINATION bin
)