cmake_minimum_required(VERSION 3.13)
project(server_prototype)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(server_prototype main.cpp PackageSizeParser.cpp PackageSizeParser.h ClientManager.cpp ClientManager.h ConsoleManager.cpp ConsoleManager.h)