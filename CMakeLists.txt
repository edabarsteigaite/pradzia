cmake_minimum_required(VERSION 3.28.1)
project(trecias)
include_directories(include)
set(SOURCES
    source/generavimas.cpp
    source/testavimas.cpp
    source/generavimas_list.cpp
    source/main.cpp
)

add_executable(trecias ${SOURCES})
