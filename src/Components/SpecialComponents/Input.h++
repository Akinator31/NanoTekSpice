//
// Created by pavel on 07/02/2026.
//

#pragma once

#include "IComponent.h++"

namespace nts
{
    /**
     * @class Input
     * @brief Class for Input Special Component
     * @details This class inherit from IComponent interface
     * @see IComponent
     */
    class Input : public IComponent
    {
        ///< Why there are 2 state wtf ??? Because we want to set the value of an Input when we simulate the program,
        /// not when the user set it via the `input=value` command.
        Tristate _currentState = Undefined; ///< Current state of the Input component (used by the compute function)
        Tristate _nextState = Undefined; ///< Next state of the Input component (used by the simulate function)

    public:
        /**
         * @brief Set the state of the Input component
         * @param value The state (True, False or Undefined)
         * @see nts::Tristate
         */
        void setValue(Tristate value);

        /**
         * @brief Get the actual value of the Input component
         * @return nts::Tristate The actual state (I think [[nodiscard]] is useless here but Clion like it)
         * @see nts::Tristate
         */
        [[nodiscard]] Tristate getValue() const;

        /**
         * @brief Simulate a tick of an Input component
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(size_t tick) override;

        /**
         * @brief Compute the result on the selected pin. Here, compute always return this->_currentState.
         * @param pin Pin to know which 'interior component' computes the result. Useless here because Input component has only one pin.
         * @return nts::Tristate The computed result, so here, just this->_currentState.
         */
        Tristate compute(size_t pin) override;

        /**
         * @brief Link a pin of another component. Useless here cause Input component is always linked to standard input (@see Circuit::assign())
         * @param pin Pin of the Input component.
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}
