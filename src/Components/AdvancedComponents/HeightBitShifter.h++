//
// Created by Noah on 19/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
namespace nts {
    class HeightBitShifter : public AComponent {
        /* PIN DEFINITIONS
            pin 1 : STROBE
            pin 2 : DATA
            pin 3 : CLOCK
            pin 4 : Q1
            pin 5 : Q2
            pin 6 : Q3
            pin 7 : Q4
            pin 8 : VSS
            pin 9 : QS
            pin 10 : Q'S
            pin 11 : Q8
            pin 12 : Q7
            pin 13 : Q6
            pin 14 : Q5
            pin 15 : OUTPUT ENABLE
            pin 16 : VDD
        */
        Tristate _prevClk = Undefined;
        Tristate _Q = Undefined;
        Tristate _QS = Undefined;
        int _value = -1;
        int _memValue = -1;

    public:
        HeightBitShifter();
        void simulate(size_t tick) override;
        void shiftValue();
        Tristate compute(size_t pin) override;
    };
}

#define CREATE_4094 std::make_unique<HeightBitShifter>();
