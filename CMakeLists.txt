cmake_minimum_required(VERSION 3.20)
project(nanotekspice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ALL_SRC "src/*.cpp")

add_executable(nanotekspice ${ALL_SRC}
        include/IComponent.h++
        src/Components/SpecialComponents/Input.cpp
        src/Components/SpecialComponents/Input.h++
        src/Factory/Factory.h++
        src/Circuit/Circuit.cpp
        src/Components/SpecialComponents/Out.cpp
        src/Components/SpecialComponents/Out.h++
        src/Circuit/Circuit.h++
        src/Components/AdvancedComponents/FourBitsAdder.cpp
        src/Components/AdvancedComponents/FourBitsAdder.h++
        src/Parser/Parser.cpp
        src/Parser/Parser.h++
        src/Errors/NanoTekSpiceErrors.cpp
        src/Errors/NanoTekSpiceErrors.h++
        src/Utils/Utils.cpp
        src/Utils/Utils.h++
        src/Parser/Chipset.cpp
        src/Parser/Link.cpp
        src/Components/SpecialComponents/True.cpp
        src/Components/SpecialComponents/True.h++
        src/Components/SpecialComponents/False.cpp
        src/Components/SpecialComponents/False.h++
        src/Components/SpecialComponents/Clock.cpp
        src/Components/SpecialComponents/Clock.h++
        src/Components/GatesComponents/GenericGatesComponents.cpp
        src/Components/GatesComponents/GenericGatesComponents.h++
        src/Components/ElementaryComponents/ElementaryComponents.cpp
        src/Components/ElementaryComponents/ElementaryComponents.h++
        src/Components/AComponent.cpp
        src/Components/AComponent.h++
        src/Components/AdvancedComponents/FullBitsAdder.cpp
        src/Components/AdvancedComponents/FullBitsAdder.h++
        src/Components/AdvancedComponents/HalfBitsAdder.cpp
        src/Components/AdvancedComponents/HalfBitsAdder.h++
        src/Components/AdvancedComponents/FlipFlop.cpp
        src/Components/AdvancedComponents/FlipFlop.h++
        src/Components/AdvancedComponents/DualFlipFlop.cpp
        src/Components/AdvancedComponents/DualFlipFlop.h++
        src/Components/AdvancedComponents/BitBinaryCounter.cpp
        src/Components/AdvancedComponents/BitBinaryCounter.h++
        src/Components/AdvancedComponents/JohnsonDecade.cpp
        src/Components/AdvancedComponents/JohnsonDecade.h++
        src/Components/AdvancedComponents/HeightBitShifter.cpp
        src/Components/AdvancedComponents/HeightBitShifter.h++
        src/Components/AdvancedComponents/HeightChannelDataSelector.cpp
        src/Components/AdvancedComponents/HeightChannelDataSelector.h++
        src/Components/AdvancedComponents/Logger.cpp
        src/Components/AdvancedComponents/Logger.h++
        src/Components/AdvancedComponents/FourBitsDecoder.cpp
        src/Components/AdvancedComponents/FourBitsDecoder.h++
        src/Components/AdvancedComponents/Rom.cpp
        src/Components/AdvancedComponents/Rom.h++
        src/Components/AdvancedComponents/Ram.cpp
        src/Components/AdvancedComponents/Ram.h++
)

target_compile_options(nanotekspice PRIVATE -Wall -Wextra -Werror)
target_include_directories(nanotekspice PRIVATE include src)

# TEST CRITERION

enable_testing()

find_library(CRITERION_LIB criterion)

if (CRITERION_LIB)
    file(GLOB_RECURSE LIB_SRC "src/*.cpp")
    list(FILTER LIB_SRC EXCLUDE REGEX "src/main\\.cpp$")

    file(GLOB_RECURSE TEST_SRC "tests/*.cpp")

    add_executable(unit_tests ${LIB_SRC} ${TEST_SRC})
    target_compile_options(unit_tests PRIVATE -Wall -Wextra --coverage)
    target_link_options(unit_tests PRIVATE --coverage)
    target_include_directories(unit_tests PRIVATE include src)
    target_link_libraries(unit_tests ${CRITERION_LIB})

    add_test(NAME unit_tests COMMAND unit_tests)
else ()
    message(STATUS "Criterion not found, unit tests will not be built.")
endif ()
