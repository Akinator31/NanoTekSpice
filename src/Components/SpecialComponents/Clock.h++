//
// Created by pavel on 09/02/2026.
//

#pragma once
#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * Class for the Clock component
     */
    class Clock : public AComponent {
        ///< Why there are 2 state wtf ??? Because we want to set the value of an Clock when we simulate the program,
        /// not when the user set it via the `input=value` command.
        Tristate _currentState = Undefined; ///< Current state of the Clock component (used by the compute function)
        Tristate _nextState = Undefined; ///< Next state of the Clock component (used by the simulate function)

    public:
        /**
         * Clock constructor
         */
        Clock();

        /**
         * Compute a specific pin of the Clock component
         * @param pin Pin of the Clock component
         * @return The value of the selected pin of the Clock component
         */
        Tristate compute(size_t pin) override;

        /**
         * @brief Set the state of the Clock component
         * @param value The state (True, False or Undefined)
         * @see nts::Tristate
         */
        void setValue(Tristate value) override;

        /**
         * @brief Simulate a tick of an Clock component
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(size_t tick) override;
    };
}

///< Macro used for create a Clock easily
#define CREATE_CLOCK std::make_unique<Clock>();
