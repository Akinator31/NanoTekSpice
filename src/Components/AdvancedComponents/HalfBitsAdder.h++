//
// Created by pavel on 12/02/2026.
//

#pragma once

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * HalfBitsAdder
     */
    class HalfBitsAdder : public AComponent {
        std::unique_ptr<IComponent> _xor_gate; ///< Internal XOR gate
        std::unique_ptr<IComponent> _and_gate; ///< Internal AND gate

    public:
        /**
         * HalfBitsAdder constructor
         */
        HalfBitsAdder();

        /**
         * Simulate a tick for the HalfBitsAdder component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the HalfBitsAdder component
         * @param pin Pin of the HalfBitsAdder component
         * @return The value of the selected pin of the HalfBitsAdder component
         */
        Tristate compute(size_t pin) override;

        /**
         * Link a component to a specific pin of the HalfBitsAdder component
         * @param pin Pin of the HalfBitsAdder component
         * @param other The other component you want to link to the HalfBitsAdder pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

///< Macro used for create a HalfBitsAdder easily
#define CREATE_HALF std::make_unique<HalfBitsAdder>()
