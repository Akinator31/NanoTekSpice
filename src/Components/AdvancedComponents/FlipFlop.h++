//
// Created by Noah on 14/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    /**
     * Class for the Flip Flop component (used by the Dual Flip Flop component)
     */
    class FlipFlop : public AComponent {
        /* PIN DEFINITIONS
            pin 1 : Q
            pin 2 : Q barre
            pin 3 : CLK
            pin 4 : RESET
            pin 5 : DATA
            pin 6 : SET
        */
        Tristate _q = Undefined; ///< Primary data output
        Tristate _qBar = Undefined; ///< Additional data output (usually the inverse of Q)
        Tristate _lastClk = Undefined; ///< Clock used for detect a positive going-edge on the internal clock

    public:
        /**
         * Flip Flop constructor
         */
        FlipFlop();

        /**
         * Simulate a tick for the Flip Flop component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the Flip Flop component
         * @param pin Pin of the Flip Flop component
         * @return The value of the selected pin of the Flip Flop component
         */
        Tristate compute(size_t pin) override;
    };
}

///< Macro used for create a Flip Flop easily
#define CREATE_SIMPLE_FLIPFLOP std::make_unique<FlipFlop>();
