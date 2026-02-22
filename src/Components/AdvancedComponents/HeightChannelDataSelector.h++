//
// Created by Noah on 22/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    class HeightChannelDataSelector : public AComponent {
        /* PIN DEFINITIONS
           pin 1 : X0
           pin 2 : X1
           pin 3 : X2
           pin 4 : X3
           pin 5 : X4
           pin 6 : X5
           pin 7 : X6
           pin 8 : VSS
           pin 9 : X7
           pin 10 : INHIBIT
           pin 11 : A
           pin 12 : B
           pin 13 : C
           pin 14 : Z
           pin 15 : OUTPUT ENABLE
           pin 16 : VDD
       */
    public:
        HeightChannelDataSelector();
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
    };
}

#define CREATE_4512 std::make_unique<HeightChannelDataSelector>();
