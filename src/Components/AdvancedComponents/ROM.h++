//
// Created by Noah on 02/03/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
#include <sys/types.h>
#include <vector>
namespace nts {
    class Rom : public AComponent {
            /* PIN DEFINITIONS
                pin 1 : A7
                pin 2 : A6
                pin 3 : A5
                pin 4 : A4
                pin 5 : A3
                pin 6 : A2
                pin 7 : A1
                pin 8 : A0
                pin 9 : Q0
                pin 10 : Q1
                pin 11 : Q2
                pin 12 : VSS
                pin 13 : Q3
                pin 14 : Q4
                pin 15 : Q5
                pin 16 : Q6
                pin 17 : Q7
                pin 18 : EP bar
                pin 19 : A10
                pin 20 : G bar
                pin 21 : VPP
                pin 22 : A9
                pin 23 : A8
                pin 24 : VCC
            */
            void computeVal();
            int _value = -1;
            std::vector<char> _romData;

        public:
            Rom();
            void simulate(size_t tick) override;
            Tristate compute(size_t pin) override;
    };
}

#define CREATE_2716 std::make_unique<nts::Rom>();
