//
// Created by Noah on 22/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    /**
     * Class for the HeightChannelDataSelector component
     */
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
        /**
         * HeightChannelDataSelector constructor
         */
        HeightChannelDataSelector();

        /**
         * Simulate a tick for the HeightChannelDataSelector component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the HeightChannelDataSelector component
         * @param pin Pin of the HeightChannelDataSelector component
         * @return The value of the selected pin of the HeightChannelDataSelector component
         */
        Tristate compute(size_t pin) override;
    };
}

///< Macro used for create a HeightChannelDataSelector easily
#define CREATE_4512 std::make_unique<HeightChannelDataSelector>();
