cmake_minimum_required(VERSION 3.17)
project(sem3_lab3_ppvis)

set(CMAKE_CXX_STANDARD 14)

add_executable(sem3_lab3_ppvis main.cpp classes/trains.cpp classes/trains.h classes/stations.cpp classes/stations.h classes/game_field.cpp classes/game_field.h classes/loader_and_checker.cpp classes/loader_and_checker.h)