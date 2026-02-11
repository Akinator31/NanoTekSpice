//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "Components/GatesComponents/GenericGatesComponents.h++"
#include "Components/ElementaryComponents/AndGate.h++"
#include "Components/ElementaryComponents/NotGate.h++"
#include "Components/ElementaryComponents/OrGate.h++"
#include "Components/ElementaryComponents/XorGate.h++"
#include "Components/SpecialComponents/Clock.h++"
#include "Components/SpecialComponents/False.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Components/SpecialComponents/True.h++"
#include "IComponent.h++"

namespace nts
{
    /**
     * @brief Factory class for create components
     */
    class Factory
    {
        ///< The map that stored component constructor functions
        std::map<std::string, std::function<std::unique_ptr<IComponent>()>> _builder = {
            {"input", []() { return std::make_unique<Input>(); }},
            {"output", []() { return std::make_unique<Out>(); }},
            {"true", []() { return std::make_unique<class True>(); }},
            {"false", []() { return std::make_unique<class False>(); }},
            {"clock", []() { return std::make_unique<Clock>(); }},
            {"and", []() { return std::make_unique<AndGate>(); }},
            {"or", []() { return std::make_unique<OrGate>(); }},
            {"xor", []() { return std::make_unique<XorGate>(); }},
            {"not", []() { return std::make_unique<NotGate>(); }},
            {"4001", []() { return CREATE_4001; }},
            {"4011", []() { return CREATE_4011; }},
            {"4030", []() { return CREATE_4030; }},
            {"4081", [](){ return CREATE_4081; }}
        };

    public:
        Factory() = default;
        /**AndGate
         *
         * @param type The of the component we want to create.
         * @throw std::exception Throw an exception if the type of the component given as parameter isn't support by the program.
         * @return std::unique_ptr<IComponent> The component newly created.
         */
        std::unique_ptr<IComponent> createComponent(const std::string& type);
    };
}
