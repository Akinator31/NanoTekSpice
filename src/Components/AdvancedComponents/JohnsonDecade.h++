//
// Created by Noah on 17/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
#include <cstddef>

namespace nts {
    /**
     * Class for the JohnsonDecade component
     */
    class JohnsonDecade : public AComponent {
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
        uint _qOn = 0; ///< Active output
        Tristate _prevClk = Undefined; ///< Internal clock for detect a positive going-edge on the component clock
        Tristate _prevCi = Undefined; ///< Internal clock for detect a positive going-edge on the Inhibit clock

    public:
        /**
         * JohnsonDecade constructor
         */
        JohnsonDecade();

        /**
         * Simulate a tick for the JohnsonDecade component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the JohnsonDecade component
         * @param pin Pin of the JohnsonDecade component
         * @return The value of the selected pin of the JohnsonDecade component
         */
        Tristate compute(size_t pin) override;
    };
}

///< Macro used for create a JohnsonDecade easily
#define CREATE_4017 std::make_unique<JohsonDecade>();
