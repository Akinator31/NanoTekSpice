//
// Created by Noah on 15/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
namespace nts {
    class BitBinaryCounter : public AComponent {
        /* PIN DEFINITIONS
            pin 1 : Q12
            pin 2 : Q6
            pin 3 : Q5
            pin 4 : Q7
            pin 5 : Q4
            pin 6 : Q3
            pin 7 : Q2
            pin 8 : GND
            pin 9 : Q1
            pin 10 : CLK
            pin 11 : RESET
            pin 12 : Q9
            pin 13 : Q8
            pin 14 : Q10
            pin 15 : Q11
            pin 16 : VCC
        */
        Tristate _lastClk = Undefined;
        int _value = 0;
        void computeVal();

    public:
        BitBinaryCounter();
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
    };
}

#define CREATE_4040 std::make_unique<BitBinaryCounter>();
