//
// Created by Noah on 02/03/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
#include <sys/types.h>
#include <vector>
namespace nts {
    /*
     * Class for the Rom component
     */
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
            void computeVal(); ///< Compute the value of the Rom component based on the address pins and the
                               ///< content of the ROM
            int _value = -1;   ///< Internal value of the Rom component
            std::vector<char> _romData; ///< Vector containing the data of the ROM loaded from the file

        public:
            /**
             * @brief Construct a new Rom object
             *
             */
            Rom();
            /**
             * @brief Simulate a tick for the Rom component
             * @param tick Actual tick of the circuit
             */
            void simulate(size_t tick) override;
            /**
             * @brief Compute a specific pin of the Rom component
             * @param pin Pin of the Rom component
             * @return The value of the selected pin of the Rom component
             */
            Tristate compute(size_t pin) override;
    };
}

///< Macro for create a Rom component
#define CREATE_2716 std::make_unique<nts::Rom>();
