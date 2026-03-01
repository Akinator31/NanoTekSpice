//
// Created by Noah on 15/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    /**
     * @brief Class for the Decade Counter advanced component
     */
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
        Tristate _lastClk = Undefined; ///< Clock used for determine the going-edge of the internal clock
        int _value = -1; ///< Value set to -1 for the recursion cases
        Tristate cachedClk = Undefined; ///< Cached clock for avoiding computation loop on the same tick
        Tristate cachedReset = Undefined; ///< Cached reset for avoiding computation loop on the same tick

        /**
         * @brief Function used to compute the internal _value use for the getBinaryValueIdx function
         */
        void _computeVal();

    public:
        /**
         * Decade counter constructor
         */
        BitBinaryCounter();

        /**
         * Simulate a tick on the Decade Counter
         * @param tick The actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific Decade Counter pin
         * @param pin Pin of the Decade Counter you want to get the value
         * @return The value of the desired pin
         */
        Tristate compute(size_t pin) override;
    };
}

///< Macro used for create a Decade Counter easily
#define CREATE_4040 std::make_unique<BitBinaryCounter>();
