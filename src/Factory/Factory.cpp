//
// Created by pavel on 07/02/2026.
//

#include "Factory.h++"

#include <algorithm>
#include <iostream>

#include "../Components/AndGate.h++"
#include "../Components/Input.h++"
#include "../Components/Out.h++"

namespace nts
{
    Factory::Factory()
    {
        this->_builder["and"] = []() { return std::make_unique<AndGate>(); };
        this->_builder["input"] = []() { return std::make_unique<Input>(); };
        this->_builder["out"] = []() { return std::make_unique<Out>(); };
    }

    std::unique_ptr<IComponent> Factory::createComponent(const std::string& type)
    {
        auto it = this->_builder.find(type);

        if (it != this->_builder.end())
            return it->second();
        return nullptr;
    }
}
