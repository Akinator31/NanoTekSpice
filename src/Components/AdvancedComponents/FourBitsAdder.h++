//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <functional>

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * Class for thr FourBitsAdder component
     */
    class FourBitsAdder : public AComponent {
        std::unique_ptr<IComponent> _fullBitsAdder0; ///< First internal full bits adder
        std::unique_ptr<IComponent> _fullBitsAdder1; ///< Second internal full bits adder
        std::unique_ptr<IComponent> _fullBitsAdder2; ///< Third internal full bits adder
        std::unique_ptr<IComponent> _fullBitsAdder3; ///< Fourth internal full bits adder

        std::map<size_t, std::function<Tristate ()>> _computeFuncs;
        ///< Mapping of the compute operations for all the pins of the component
        std::map<size_t, std::function<void (IComponent& other, size_t otherPin)>> _setLinksFuncs;
        ///> Mapping the link operations for all the pins of the component

    public:
        /**
         * Four Bits Adder constructor
         */
        FourBitsAdder();

        /**
         * Simulate a tick for the 4BitsAdder component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the 4BitsAdder component
         * @param pin Pin of the 4BitsAdder component
         * @return The value of the selected pin of the 4BitsAdder component
         */
        Tristate compute(size_t pin) override;

        /**
         * Link a component to a specific pin of the 4BitsAdder component
         * @param pin Pin of the 4BitsAdder component
         * @param other The other component you want to link to the 4BitsAdder pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

///< Macro used for create a 4BitsAdder easily
#define CREATE_4008 std::make_unique<FourBitsAdder>();
