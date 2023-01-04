cmake_minimum_required(VERSION 3.22)
set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..)


project(LastFall VERSION 1.1.0)
add_subdirectory(${BASE_DIRECTORY}/../CoreEngine/projects/cmake CoreEngine)
add_executable(LastFall)


set_target_properties(
    LastFall PROPERTIES
    C_STANDARD 17
    CXX_STANDARD 20
    DEBUG_POSTFIX _debug
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH $ORIGIN
)


target_sources(
    LastFall PRIVATE
    ${BASE_DIRECTORY}/source/cDoor.cpp
    ${BASE_DIRECTORY}/source/cEnemy.cpp
    ${BASE_DIRECTORY}/source/cField.cpp
    ${BASE_DIRECTORY}/source/cGame.cpp
    ${BASE_DIRECTORY}/source/cInterface.cpp
    ${BASE_DIRECTORY}/source/cLevel.cpp
    ${BASE_DIRECTORY}/source/cPlayer.cpp
    ${BASE_DIRECTORY}/source/cShadow.cpp
    ${BASE_DIRECTORY}/source/cTile.cpp
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


if(EMSCRIPTEN)


    set_target_properties(
        LastFall PROPERTIES
        SUFFIX .html
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/emscripten/
    )


else()


    set_target_properties(
        LastFall PROPERTIES
        SUFFIX .elf
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/linux_x86_64/
    )


endif()