cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)


# install()

add_executable(task src/task.cpp)
target_link_libraries(task OpenMP::OpenMP_CXX )
