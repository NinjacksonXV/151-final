cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(OPENAL_PATH "C:/Development/Tools/ucrt64/bin/libopenal-1.dll" CACHE PATH "Path to OpenAL directory")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(CMakeSFMLProject ${SOURCES})
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "C:/Development/Tools/ucrt64/bin/libopenal-1.dll" $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
