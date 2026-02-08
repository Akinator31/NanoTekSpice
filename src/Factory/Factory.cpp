//
// Created by pavel on 07/02/2026.
//

#include "Factory.h++"

#include <algorithm>

#include "Components/ElementaryComponents/AndGate.h++"

namespace nts
{
    std::unique_ptr<IComponent> Factory::createComponent(const std::string& type)
    {
        auto it = this->_builder.find(type);

        if (it != this->_builder.end())
            return it->second();
        return nullptr;
    }
}
