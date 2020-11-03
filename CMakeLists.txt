cmake_minimum_required(VERSION 3.17)
project(sem3_lab3_ppvis)

set(CMAKE_CXX_STANDARD 14)

add_executable(sem3_lab3_ppvis main.cpp classes/trains.cpp classes/trains.h classes/stations.cpp classes/stations.h classes/game_field.cpp classes/game_field.h classes/Loader.cpp classes/Loader.h classes/Checker.cpp classes/Checker.h classes/Error.cpp classes/Error.h)