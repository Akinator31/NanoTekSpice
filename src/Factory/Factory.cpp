//
// Created by pavel on 07/02/2026.
//

#include "Factory.h++"

#include <algorithm>

namespace nts {
    std::unique_ptr<IComponent> Factory::createComponent(const std::string& type) {
        if (const auto it = this->_builder.find(type); it != this->_builder.end())
            return it->second();
        return nullptr;
    }
}
