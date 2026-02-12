//
// Created by pavel on 09/02/2026.
//

#pragma once
#include "IComponent.h++"

namespace nts {
    class False : public IComponent {
        Tristate _currentState = Tristate::False;
        ///< Current state of the False component (used by the compute function)

    public:
        /**
         * @brief Simulate a tick of a False component (does nothing for this component)
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(size_t tick) override;

        /**
         * @brief Compute the result on the selected pin. Here, we always return Tristate::False;
         * @param pin Pin to know which 'interior component' computes the result. Useless here because False component has only one pin.
         * @return nts::Tristate The computed result, so here, just Tristate::False.
         */
        Tristate compute(size_t pin) override;

        /**
         * @brief Link a pin of another component.
         * @param pin Pin of the False component. Useless here
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}
