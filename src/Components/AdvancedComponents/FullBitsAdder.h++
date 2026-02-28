//
// Created by pavel on 13/02/2026.
//

#pragma once
#include "Components/AComponent.h++"

namespace nts {
    /**
     * Class for thr FullBitsAdder component
     */
    class FullBitsAdder : public AComponent {
        std::unique_ptr<IComponent> _xor_gate1; ///< First internal XOR gate
        std::unique_ptr<IComponent> _xor_gate2; ///< Second internal XOR gate
        std::unique_ptr<IComponent> _and_gate1; ///< First internal AND gate
        std::unique_ptr<IComponent> _and_gate2; ///< Second internal XOR gate
        std::unique_ptr<IComponent> _or_gate; ///< Internal OR gate

    public:
        /**
         * FullBitsAdder constructor
         */
        FullBitsAdder();

        /**
         * Simulate a tick for the FullBitsAdder component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the FullBitsAdder component
         * @param pin Pin of the FullBitsAdder component
         * @return The value of the selected pin of the FullBitsAdder component
         */
        Tristate compute(size_t pin) override;

        /**
         * Link a component to a specific pin of the FullBitsAdder component
         * @param pin Pin of the FullBitsAdder component
         * @param other The other component you want to link to the FullBitsAdder pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

///< Macro used for create a FullBitsAdder easily
#define CREATE_FULL std::make_unique<FullBitsAdder>()
