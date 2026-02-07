//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <map>

#include "IComponent.h++"

namespace nts
{
    class AndGate: public IComponent
    {
        std::map<std::size_t, ComponentLink> _input;

        Tristate _prevValue = Undefined;
        std::size_t _lastComputedTick = -1;
        std::size_t _lastSimulatedTick = 0;

    public:
        AndGate() = default;
        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override;
        static Tristate computeAndOperation(Tristate first, Tristate second);
    };
}
