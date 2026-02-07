//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <map>

#include "IComponent.h++"

namespace nts
{
    class Circuit
    {
        size_t _tick = 0;
        std::pmr::map<std::string, std::unique_ptr<IComponent>> componentList= {};

    public:
        void simulate();
        void display() const;
        void add_component(const std::string& name, std::unique_ptr<IComponent> component);
    };
}