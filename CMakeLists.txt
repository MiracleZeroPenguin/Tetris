CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
project(Tetris C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")


aux_source_directory(Utils DIR_UTILS)
aux_source_directory(libgraphics DIR_LIBS)
include_directories(Utils include)
 add_executable(${PROJECT_NAME} ${DIR_UTILS} ${DIR_LIBS} tetris.c)