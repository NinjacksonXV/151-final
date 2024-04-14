# 151 Final
Project for CS-151 final at North Idaho College, written in C++ and using [SFML](https://www.sfml-dev.org/). 

## Build Instructions
Use CMake to first pull SFML and build it locally; this will generate the needed makefile for the project itself, which you can then build. It is recommended to use the [VSCode CMake-Tools](https://code.visualstudio.com/docs/cpp/cmake-linux) extension if you are unfamiliar with using CMake from the command line. 

> [!IMPORTANT] 
> Currently, it's required to manually move any shaders (i.e. stars.frag) to `build/bin`. While this can be automated with CMake down the line, it makes editing shaders awkward; since the shaders are loaded at runtime, it's possible to modify the shaders without rebuilding the project, which is very quick. 
>
> One simple solution is to make a symbolic link for the file. Ideally, such workarounds won't be necessary later. 