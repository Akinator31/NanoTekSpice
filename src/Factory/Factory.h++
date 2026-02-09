//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "IComponent.h++"
#include "Components/ElementaryComponents/AndGate.h++"
#include "Components/ElementaryComponents/OrGate.h++"
#include "Components/SpecialComponents/Clock.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Components/SpecialComponents/True.h++"
#include "Components/SpecialComponents/False.h++"

namespace nts
{
    /**
     * @brief Factory class for create components
     */
    class Factory
    {
        ///< The map that stored component constructor functions
        std::map<std::string, std::function<std::unique_ptr<IComponent> ()>> _builder = {
            {"input", []() { return std::make_unique<Input>(); }},
            {"clock", []() { return std::make_unique<Clock>(); }},
            {"true", []() { return std::make_unique<class True>(); }},
            {"false", []() { return std::make_unique<class False>(); }},
            {"output", []() { return std::make_unique<Out>(); }},
            {"and", []() { return std::make_unique<AndGate>(); }},
            {"or", []() { return std::make_unique<OrGate>(); }},
        };

    public:
        Factory() = default;
        /**
         *
         * @param type The of the component we want to create.
         * @throw std::exception Throw an exception if the type of the component given as parameter isn't support by the program.
         * @return std::unique_ptr<IComponent> The component newly created.
         */
        std::unique_ptr<IComponent> createComponent(const std::string& type);
    };
}
