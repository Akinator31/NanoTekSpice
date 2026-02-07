//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "IComponent.h++"

namespace nts
{
    class Factory
    {
        std::map<std::string, std::function<std::unique_ptr<IComponent> ()>> _builder = {};

    public:
        Factory();
        std::unique_ptr<IComponent> createComponent(const std::string &type);
    };
}
