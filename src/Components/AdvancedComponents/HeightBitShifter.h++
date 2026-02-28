//
// Created by Noah on 19/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    /**
     * Class for the 8BitsShifter component
     */
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
        Tristate _prevClk = Undefined; ///< Clock used for detect a positive going-edge on the internal clock
        Tristate _Q = Undefined; ///< Output data
        Tristate _QS = Undefined; ///< Used for add a shifter
        int _value = -1; ///< Internal value
        int _memValue = -1; ///< Internal stored value

    public:
        /**
         * HeightBitShifter constructor
         */
        HeightBitShifter();

        /**
         * Simulate a tick for the HeightBitShifter component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Shift a value.
         */
        void shiftValue();

        /**
         * Compute a specific pin of the HeightBitShifter component
         * @param pin Pin of the HeightBitShifter component
         * @return The value of the selected pin of the HeightBitShifter component
         */
        Tristate compute(size_t pin) override;
    };
}

///< Macro used for create a HeightBitShifter easily
#define CREATE_4094 std::make_unique<HeightBitShifter>();
