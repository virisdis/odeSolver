cmake_minimum_required (VERSION 3.0)
project (odeSolver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -lpython3.10")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(
                    ${PROJECT_SOURCE_DIR}/include
                   )
                   
add_executable(odeSolver "main.cpp")
