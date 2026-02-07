//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <map>
#include <memory>
#include <string>

namespace nts
{
    enum Tristate
    {
        Undefined = -1,
        True = true,
        False = false
    };

    class IComponent
    {
    public:
        virtual ~IComponent() = default;

        virtual void simulate(size_t tick) = 0;
        virtual Tristate compute(size_t pin) = 0;
        virtual void setLink(size_t pin, IComponent &other, size_t otherPin) = 0;
    };

    struct ComponentLink
    {
        IComponent *component = nullptr;
        size_t pin = 0;
    };

    class Circuit
    {
        size_t _tick = 0;
        std::pmr::map<std::string, std::unique_ptr<IComponent>> componentList= {};

    public:
        void simulate();
        void display();
        void add_component(const std::string& name, std::unique_ptr<IComponent> component);
    };
}
