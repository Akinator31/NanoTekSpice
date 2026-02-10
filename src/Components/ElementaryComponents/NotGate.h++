//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <map>

#include "IComponent.h++"

namespace nts {
    /**
     * @class NotGate
     * @brief Class for NotGate Elementary Component
     * @details This class inherit from IComponent interface
     * @see IComponent
     */
    class NotGate : public IComponent {
        std::map<std::size_t, ComponentLink> _input; ///< Map that stored linked component.

        Tristate _prevValue = Undefined;    ///< Previously computed value to avoid recomputation.
        std::size_t _lastComputedTick = -1; ///< Last computed tick for compare if the value has already been
                                            ///< computed. In this case, we just return the _prevValue.
        std::size_t _lastSimulatedTick = 0; ///< Last simulated tick.

      public:
        /**
         * @brief NotGate constructor
         */
        NotGate() = default;

        /**
         * @brief Simulate a tick of an NotGate component
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Compute the result on the selected pin.
         * @param pin Pin to know which 'interior component' computes the result.
         * @return nts::Tristate The computed result.
         */
        Tristate compute(std::size_t pin) override;

        /**
         * @brief Link a pin of another component.
         * @param pin Pin of the NotGate component.
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override;

        /**
         * @brief Compute an ! operation
         * @param first First operand
         * @param second Second operand
         * @return The result of the ! operation
         */
        static Tristate computeNotOperation(Tristate value);
    };
} // namespace nts
