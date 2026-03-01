//
// Created by Noah on 15/02/2026.
//
#pragma once

#include "Components/AComponent.h++"
#include "IComponent.h++"
#include <memory>

namespace nts {
    /**
     * Class for the Dual Flip Flop component
     */
    class DualFlipFlop : public AComponent {
        std::unique_ptr<IComponent> _flipflop1; ///< First internal Flip Flop component
        std::unique_ptr<IComponent> _flipflop2; ///< Second internal Flip Flop component

    public:
        /**
         * Dual Flip Flop constructor
         */
        DualFlipFlop();

        /**
         * Simulate a tick for the Dual Flip Flop component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the Dual Flip Flop component
         * @param pin Pin of the Dual Flip Flop component
         * @return The value of the selected pin of the Dual Flip Flop component
         */
        Tristate compute(size_t pin) override;

        /**
         * Link a component to a specific pin of the Dual Flip Flop component
         * @param pin Pin of the Dual Flip Flop component
         * @param other The other component you want to link to the Dual Flip Flop pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

///< Macro used for create a Decade Counter easily
#define CREATE_4013 std::make_unique<DualFlipFlop>();
