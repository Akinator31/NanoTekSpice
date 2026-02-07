//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <memory>

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
}
