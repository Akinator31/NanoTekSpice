//
// Created by Noah on 14/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    class FlipFlop : public AComponent {
        /* PIN DEFINITIONS
            pin 1 : Q
            pin 2 : Q barre
            pin 3 : CLK
            pin 4 : RESET
            pin 5 : DATA
            pin 6 : SET
        */
        Tristate _q = Undefined;
        Tristate _qBar = Undefined;
        Tristate _lastClk = Undefined;

    public:
        FlipFlop();
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
    };
}

#define CREATE_SIMPLE_FLIPFLOP std::make_unique<FlipFlop>();
