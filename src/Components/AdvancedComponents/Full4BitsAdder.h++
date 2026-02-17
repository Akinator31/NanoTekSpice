//
// Created by pavel on 13/02/2026.
//

#pragma once
#include "Components/AComponent.h++"

namespace nts {
    class Full4BitsAdder : public AComponent {
        std::unique_ptr<IComponent> _xor_gate1;
        std::unique_ptr<IComponent> _xor_gate2;
        std::unique_ptr<IComponent> _and_gate1;
        std::unique_ptr<IComponent> _and_gate2;
        std::unique_ptr<IComponent> _or_gate;

    public:
        Full4BitsAdder();

        void simulate(size_t tick) override;

        Tristate compute(size_t pin) override;

        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

#define CREATE_FULL std::make_unique<Full4BitsAdder>()
