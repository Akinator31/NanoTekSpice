//
// Created by pavel on 07/02/2026.
//

#pragma once
#include "IComponent.h++"

namespace nts
{
    class Input: public IComponent
    {
        Tristate _currentState = Undefined;
        Tristate _nextState = Undefined;

    public:
        void setValue(Tristate value);
        Tristate getValue() const;
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}
