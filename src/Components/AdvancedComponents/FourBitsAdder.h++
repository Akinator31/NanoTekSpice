//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <functional>

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    class FourBitsAdder : public AComponent {
        std::unique_ptr<IComponent> _halfBitsAdder;
        std::unique_ptr<IComponent> _fullBitsAdder1;
        std::unique_ptr<IComponent> _fullBitsAdder2;
        std::unique_ptr<IComponent> _fullBitsAdder3;

        std::map<size_t, std::function<Tristate ()>> _computeFuncs;
        std::map<size_t, std::function<void (IComponent& other, size_t otherPin)>> _setLinksFuncs;

    public:
        FourBitsAdder();

        void simulate(size_t tick) override;

        Tristate compute(size_t pin) override;

        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

#define CREATE_4008 std::make_unique<FourBitsAdder>();
