cmake_minimum_required(VERSION 3.31)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(ENGINE_DIRECTORY ${BASE_DIRECTORY}/../core-engine)

project(
    LastFall
    VERSION 1.2.0
    DESCRIPTION "Tricky arcade puzzler made for Ludum Dare 49"
    HOMEPAGE_URL "https://www.maus-games.at"
    LANGUAGES C CXX
)

add_subdirectory(${ENGINE_DIRECTORY}/projects/cmake CoreEngine)
add_executable(LastFall)

set_target_properties(
    LastFall PROPERTIES
    C_STANDARD 17
    CXX_STANDARD 23
    CXX_SCAN_FOR_MODULES OFF
    DEBUG_POSTFIX _debug
)

target_sources(
    LastFall PRIVATE
    ${BASE_DIRECTORY}/source/Door.cpp
    ${BASE_DIRECTORY}/source/Enemy.cpp
    ${BASE_DIRECTORY}/source/Field.cpp
    ${BASE_DIRECTORY}/source/Game.cpp
    ${BASE_DIRECTORY}/source/Interface.cpp
    ${BASE_DIRECTORY}/source/Level.cpp
    ${BASE_DIRECTORY}/source/Player.cpp
    ${BASE_DIRECTORY}/source/Shadow.cpp
    ${BASE_DIRECTORY}/source/Tile.cpp
    ${BASE_DIRECTORY}/source/application.cpp
    ${BASE_DIRECTORY}/source/main.cpp
)

target_include_directories(
    LastFall PRIVATE
    ${BASE_DIRECTORY}/source
)

target_precompile_headers(
   LastFall PRIVATE
   $<$<COMPILE_LANGUAGE:CXX>: ${BASE_DIRECTORY}/source/main.h>
)

target_link_libraries(
    LastFall PRIVATE
    CoreEngine
)

if(CORE_EMSCRIPTEN)

    set_target_properties(
        LastFall PROPERTIES
        SUFFIX .html
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/emscripten
    )

else()

    set_target_properties(
        LastFall PROPERTIES
        SUFFIX .elf
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/linux_x86_64
    )

    if(NOT CORE_DEBUG)

        set_target_properties(
            LastFall PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            INSTALL_RPATH $ORIGIN
        )

        add_custom_command(
            TARGET LastFall POST_BUILD
            COMMAND ${ENGINE_DIRECTORY}/tools/scripts/extract_symbols.sh $<TARGET_FILE:LastFall>
        )

    endif()

endif()