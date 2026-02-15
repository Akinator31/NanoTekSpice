//
// Created by Noah on 15/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
#include <memory>

namespace nts {
    class DualFlipFlop : public AComponent {
        std::unique_ptr<IComponent> _flipflop1;
        std::unique_ptr<IComponent> _flipflop2;

    public:
        DualFlipFlop();
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

#define CREATE_4013 std::make_unique<DualFlipFlop>();
