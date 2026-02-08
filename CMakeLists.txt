cmake_minimum_required(VERSION 3.20)
project(nanotekspice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ALL_SRC "src/*.cpp")

add_executable(nanotekspice ${ALL_SRC}
        include/IComponent.h++
        src/Components/ElementaryComponents/AndGate.cpp
        src/Components/ElementaryComponents/AndGate.h++
        src/Components/SpecialComponents/Input.cpp
        src/Components/SpecialComponents/Input.h++
        src/Factory/Factory.cpp
        src/Factory/Factory.h++
        src/Circuit/Circuit.cpp
        src/Components/SpecialComponents/Out.cpp
        src/Components/SpecialComponents/Out.h++
        src/Circuit/Circuit.h++
        src/Components/AdvancedComponents/FourBitsAdder.cpp
        src/Components/AdvancedComponents/FourBitsAdder.h++
        src/Components/GatesComponents/FourNorGates.cpp
        src/Components/GatesComponents/FourNorGates.h++
)

target_compile_options(nanotekspice PRIVATE -Wall -Wextra -Werror)
target_include_directories(nanotekspice PRIVATE include src)