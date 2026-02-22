//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "Components/AdvancedComponents/BitBinaryCounter.h++"
#include "Components/AdvancedComponents/DualFlipFlop.h++"
#include "Components/AdvancedComponents/FlipFlop.h++"
#include "Components/AdvancedComponents/FourBitsAdder.h++"
#include "Components/AdvancedComponents/Full4BitsAdder.h++"
#include "Components/AdvancedComponents/Half4bitsAdder.h++"
#include "Components/AdvancedComponents/HeightBitShifter.h++"
#include "Components/AdvancedComponents/HeightChannelDataSelector.h++"
#include "Components/AdvancedComponents/JohnsonDecade.h++"
#include "Components/ElementaryComponents/ElementaryComponents.h++"
#include "Components/GatesComponents/GenericGatesComponents.h++"
#include "Components/SpecialComponents/Clock.h++"
#include "Components/SpecialComponents/False.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Components/SpecialComponents/True.h++"
#include "IComponent.h++"
#include "Utils/Utils.h++"

namespace nts {
    /**
     * @brief Factory class for create components
     */
    class Factory {
        ///< The map that stored component constructor functions
        std::map<std::string, std::function<std::unique_ptr<IComponent>()>> _builder = {
            { "input", [] { return std::make_unique<Input>(); } },
            { "output", [] { return std::make_unique<Out>(); } },
            { "true", [] { return std::make_unique<class True>(); } },
            { "false", [] { return std::make_unique<class False>(); } },
            { "clock", [] { return std::make_unique<Clock>(); } },
            { "and", [] { return CREATE_AND; } },
            { "or", [] { return CREATE_OR; } },
            { "xor", [] { return CREATE_XOR; } },
            { "nor", [] { return CREATE_NOR; } },
            { "nand", [] { return CREATE_NAND; } },
            { "not", [] { return CREATE_NOT; } },
            { "4001", [] { return CREATE_4001; } },
            { "4011", [] { return CREATE_4011; } },
            { "4030", [] { return CREATE_4030; } },
            { "4069", [] { return CREATE_4069; } },
            { "4071", [] { return CREATE_4071; } },
            { "4081", [] { return CREATE_4081; } },
            { "halfBitsAdder", [] { return CREATE_HALF; } },
            { "fullBitsAdder", [] { return CREATE_FULL; } },
            { "4008", [] { return CREATE_4008; } },
            { "flipflop", [] { return CREATE_SIMPLE_FLIPFLOP; } },
            { "4013", [] { return CREATE_4013; } },
            { "4040", [] { return CREATE_4040; } },
            { "4017", [] { return CREATE_4017; } },
            { "4094", [] { return CREATE_4094 } },
            { "4512", [] { return CREATE_4512 } },
        };

    public:
        Factory() = default;
        /**
         * Factory constructor. You can use it to create every component.
         * @param type The of the component we want to create.
         * @throw std::exception Throw an exception if the type of the component given as parameter isn't
         * support by the program.
         * @return std::unique_ptr<IComponent> The component newly created.
         */
        std::unique_ptr<IComponent> createComponent(const std::string& type);
    };
} // namespace nts
