cmake_minimum_required(VERSION 3.19)

project(GameOfLife)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

add_executable(GameOfLifeInfBoard InfiniteBoard.cpp ${INCLUDE_DIR}/GameOfLifeState.cpp)