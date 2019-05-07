cmake_minimum_required(VERSION 3.13)
project(server_prototype)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread )

include_directories(. "/usr/include/cppconn")
link_directories("/usr/lib/" "mysqlcppconn")


add_executable(server_prototype main.cpp PackageSizeParser.cpp PackageSizeParser.h ConnectionManager.cpp ConnectionManager.h ConsoleManager.cpp ConsoleManager.h ClientStructure.h DataBaseConnection.cpp DataBaseConnection.h ServerController.cpp ServerController.h Offer.cpp Offer.h Event.cpp Event.h Group.cpp Group.h User.cpp User.h Vote.cpp Vote.h Comment.cpp Comment.h RequestFlag.h ResponseFlag.h)

target_link_libraries(server_prototype mysqlcppconn)