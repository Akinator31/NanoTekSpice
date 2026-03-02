//
// Created by Noah on 01/03/2026.
//

#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {

    class FourBitsDecoder : public AComponent {
            /* PIN DEFINITIONS
                pin 1 : STROBE
                pin 2 : A
                pin 3 : B
                pin 4 : Q8
                pin 5 : Q7
                pin 6 : Q6
                pin 7 : Q5
                pin 8 : Q4
                pin 9 : Q3
                pin 10 : Q2
                pin 11 : Q1
                pin 12 : VSS
                pin 13 : Q14
                pin 14 : Q13
                pin 15 : Q16
                pin 16 : Q15
                pin 17 : Q10
                pin 18 : Q9
                pin 19 : Q12
                pin 20 : Q11
                pin 21 : C
                pin 22 : D
                pin 23 : INHIB
                pin 24 : VDD
            */
        public:
            FourBitsDecoder();
            virtual ~FourBitsDecoder() = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

        private:
            void computeVal();

            int _value = -1;
            Tristate _lastClk = Undefined;
            std::size_t _lastSimulatedTick = 0;
    };
}

#define CREATE_4514 std::make_unique<nts::FourBitsDecoder>()
