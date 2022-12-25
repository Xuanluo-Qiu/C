cmake_minimum_required(VERSION 3.13)
project(InCircle C)

set(CMAKE_C_STANDARD 11)

set(MY_LIBRARY_DIR /usr/local/Cellar)

set(SDL_DIR ${MY_LIBRARY_DIR}/sdl2/2.26.0)
include_directories(${SDL_DIR}/include/SDL2)
link_directories(${SDL_DIR}/lib/)

set(SDL2_image /usr/local/Cellar/sdl2_image/2.6.2)
include_directories(${SDL2_image}/include/)
link_directories(${SDL2_image}/lib/)

link_libraries(SDL2 SDL2_image)

set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(InCircle main.c Resource.c Resource.h Eyeball.c Eyeball.h DisplayObject.c DisplayObject.h)