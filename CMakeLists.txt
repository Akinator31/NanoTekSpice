cmake_minimum_required(VERSION 3.20)
project(nanotekspice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ALL_SRC "src/*.cpp")

add_executable(nanotekspice ${ALL_SRC}
        include/IComponent.h++
        src/Components/AndGate.cpp
        src/Components/AndGate.h++
        src/Components/Input.cpp
        src/Components/Input.h++
        src/Factory/Factory.cpp
        src/Factory/Factory.h++
        src/Circuit.cpp
        src/Components/Out.cpp
        src/Components/Out.h++
)

target_compile_options(nanotekspice PRIVATE -Wall -Wextra -Werror)
target_include_directories(nanotekspice PRIVATE include)