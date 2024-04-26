cmake_minimum_required(VERSION 3.16)
project(Asteroids LANGUAGES CXX)

set(OPENAL_PATH "C:/msys64/ucrt64/bin/libopenal-1.dll" CACHE PATH "Path to OpenAL directory")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Asteroids ${SOURCES})
target_link_libraries(Asteroids PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

target_compile_features(Asteroids PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET Asteroids
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "C:/msys64/ucrt64/bin/libopenal-1.dll" $<TARGET_FILE_DIR:Asteroids>
        VERBATIM)
endif()

install(TARGETS Asteroids)
