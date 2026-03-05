//
// Created by Noah on 01/03/2026.
//

#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    /**
     * FourBitsDecoder
     */
    class FourBitsDecoder : public AComponent {
            /* PIN DEFINITIONS
                pin 1 : STROBE
                pin 2 : A
                pin 3 : B
                pin 4 : Q7
                pin 5 : Q6
                pin 6 : Q5
                pin 7 : Q4
                pin 8 : Q3
                pin 9 : Q1
                pin 10 : Q2
                pin 11 : Q0
                pin 12 : VSS
                pin 13 : Q13
                pin 14 : Q12
                pin 15 : Q15
                pin 16 : Q14
                pin 17 : Q9
                pin 18 : Q8
                pin 19 : Q11
                pin 20 : Q10
                pin 21 : C
                pin 22 : D
                pin 23 : INHIB
                pin 24 : VDD
            */
        public:
            /**
             * Constructor for FourBitsDecoder
             */
            FourBitsDecoder();
            virtual ~FourBitsDecoder() = default;

            /**
             * Simulate a tick for the FourBitsDecoder component
             * @param tick Actual tick of the circuit
             */
            void simulate(std::size_t tick) override;
            /**
             * Compute a specific pin of the FourBitsDecoder component
             * @param pin Pin of the FourBitsDecoder component
             * @return The value of the selected pin of the FourBitsDecoder component
             */
            Tristate compute(std::size_t pin) override;

        private:
            /**
             * Compute the value of the FourBitsDecoder component based on its inputs
             * @param strobe Value of the strobe pin
             */
            void computeVal(Tristate& strobe);

            int _value = -1; ///< Internal value of the FourBitsDecoder component, -1 for Undefined, -2 for
                             ///< False, 0-15 for True
            Tristate _lastClk = Undefined;      ///< Last clock value
            std::size_t _lastSimulatedTick = 0; ///< Last simulated tick
    };
}

///< Macro used for create a FourBitsDecoder easily
#define CREATE_4514 std::make_unique<nts::FourBitsDecoder>()
