//
// Created by pavel on 09/02/2026.
//

#pragma once
#include "IComponent.h++"

namespace nts {
    class True : public IComponent {
        Tristate _currentState = Tristate::True; ///< Current state of the True component (used by the compute function)

    public:
        /**
         * @brief Simulate a tick of a True component (does nothing for this component)
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(size_t tick) override;

        /**
         * @brief Compute the result on the selected pin. Here, we always return Tristate::True;
         * @param pin Pin to know which 'interior component' computes the result. Useless here because True component has only one pin.
         * @return nts::Tristate The computed result, so here, just Tristate::True.
         */
        Tristate compute(size_t pin) override;

        /**
         * @brief Link a pin of another component.
         * @param pin Pin of the True component. Useless here
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}
