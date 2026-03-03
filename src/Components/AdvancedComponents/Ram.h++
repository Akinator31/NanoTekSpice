//
// Created by pavel on 03/03/2026.
//

#pragma once
#include <vector>

#include "Components/AComponent.h++"

namespace nts {
    /**
     * Class for the Ram component
     */
    class Ram : public AComponent {
        std::vector<std::array<Tristate, 8>> _memory; ///< Ram memory (1k * 8bits)

        ///< Store component links
        std::map<size_t, std::vector<std::pair<IComponent*, size_t>>> _links;

        /**
         * Enum for better understanding of the component behavior
         */
        enum ramPinout {
            A7 = 1,
            A6 = 2,
            A5 = 3,
            A4 = 4,
            A3 = 5,
            A2 = 6,
            A1 = 7,
            A0 = 8,
            DQ0 = 9,
            DQ1 = 10,
            DQ2 = 11,
            VSS = 12,
            DQ3 = 13,
            DQ4 = 14,
            DQ5 = 15,
            DQ6 = 16,
            DQ7 = 17,
            NOT_CE = 18,
            NC = 19,
            NOT_OE = 20,
            NOT_WE = 21,
            A9 = 22,
            A8 = 23,
            VCC = 24,
        };

    public:
        /**
         * Ram constructor
         */
        Ram();

        /**
         * Simulate a tick for the Ram component (used for writing in the memory)
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the Ram component
         * @param pin Pin of the Logger component
         * @return The value of the selected pin of the Logger component
         */
        Tristate compute(size_t pin) override;

        /**
         * Link a component to a specific pin of the Ram component
         * @param pin Pin of the Logger component
         * @param other The other component you want to link to the Logger pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;

        /**
         * Write data computed from DQx pins to a specific address in the memory
         * @param address Address where data will be stored in the memory
         */
        void writeToMemory(int address);

        /**
         * Compute the address from Ax pins
         * @return A specific index for the memory
         */
        int getAddress();

        /**
         * Compute a specific pin without computing an output
         * @param pin The specific pin
         * @return The value computed on the specific pin
         */
        Tristate getInputOnPin(size_t pin);
    };
}

///< Macro used for create a Ram easily
#define CREATE_4801 std::make_unique<nts::Ram>();
