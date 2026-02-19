//
// Created by Noah on 17/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
#include <cstddef>
namespace nts {
    class JohsonDecade : public AComponent {
        /* PIN DEFINITIONS
            pin 1 : Q5
            pin 2 : Q1
            pin 3 : Q0
            pin 4 : Q2
            pin 5 : Q6
            pin 6 : Q7
            pin 7 : Q3
            pin 8 : GND
            pin 9 : Q8
            pin 10 : Q4
            pin 11 : Q9
            pin 12 : CO
            pin 13 : CI
            pin 14 : CLK
            pin 15 : MR
            pin 16 : VDD
        */
        uint _qOn = 0;
        Tristate _prevClk = Undefined;
        Tristate _prevCi = Undefined;

    public:
        JohsonDecade();
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
    };
}

#define CREATE_4017 std::make_unique<JohsonDecade>();
