cmake_minimum_required(VERSION 3.13)
project(RenderText C)

set(CMAKE_C_STANDARD 11)


# SDL2
set(SDL_DIR /usr/local/Cellar/sdl2/2.26.0)
include_directories(${SDL_DIR}/include/SDL2)
link_directories(${SDL_DIR}/lib/)

# SDL2_ttf
set(SDL2_ttf /usr/local/Cellar/sdl2_ttf/2.20.1)
include_directories(${SDL2_ttf}/include/)
link_directories(${SDL2_ttf}/lib/)

link_libraries(SDL2)
link_libraries(SDL2_ttf)

set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(RenderText main.c DisplayObject.c DisplayObject.h Text.c Text.h)