cmake_minimum_required(VERSION 3.10)
project(mime-types VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(mime-types main.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(unofficial-libmagic REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::libmagic::libmagic)