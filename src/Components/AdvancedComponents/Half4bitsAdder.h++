//
// Created by pavel on 12/02/2026.
//

#pragma once

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    class Half4bitsAdder : public AComponent {
        std::unique_ptr<IComponent> _xor_gate;
        std::unique_ptr<IComponent> _and_gate;

    public:
        Half4bitsAdder();

        void simulate(size_t tick) override;

        Tristate compute(size_t pin) override;

        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

#define CREATE_HALF std::make_unique<Half4bitsAdder>();
